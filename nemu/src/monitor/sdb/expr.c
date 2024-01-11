/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ, TK_NEQ, TK_AND,

  /* TODO: Add more token types */
  TK_NUM, TK_HEX, TK_REG, TK_DEREF
};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  {"\\(", '('},         // left parenthesis
  {"\\)", ')'},         // right parenthesis
  {"\\*", '*'},         // multiply
  {"\\/", '/'},         // divide
  {"\\-", '-'},         // minus
  {"[0-9]+", TK_NUM},     // number
  {"0[xX][0-9a-fA-F]+", TK_HEX},     // hex number
  {"\\$[a-zA-Z_]+", TK_REG},     // register
  {"==", TK_EQ},        // equal
  {"!=", TK_NEQ},       // not equal
  {"&&", TK_AND},       // and

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"==", TK_EQ},        // equal
};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

static int is_expr(int type)
{
  switch (type) {
    case TK_NUM:
    case TK_HEX:
    case TK_REG:
    case ')' :
      return 1;
    default:
      return 0;
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[65536] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;
static int illegal __attribute__((used)) = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  init_regex();

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);
        
        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE: break;
          case '*': {
            if (nr_token == 0) {
              tokens[nr_token].type = TK_DEREF;
              sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
              nr_token ++;
            }
            else if (is_expr(tokens[nr_token - 1].type) == 1) {
              tokens[nr_token].type = '*';
              sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
              nr_token ++;
            }
            else {
              tokens[nr_token].type = TK_DEREF;
              sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
              nr_token ++;
            }
            break;
          }
          default: {
            tokens[nr_token].type = rules[i].token_type;
            sprintf(tokens[nr_token].str, "%.*s", substr_len, substr_start);
            nr_token ++;
          }
        }
        
        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

static bool check_parentheses(int p, int q) {
  int parentheses = 0;
  int false_parentheses = 0;
  if (tokens[p].type != '(' || tokens[q].type != ')') {
    false_parentheses = 1;
  }
  for (int i = p; i <= q; i++) {
    if (tokens[i].type == '(') {
      parentheses++;
    }
    else if (tokens[i].type == ')') {
      parentheses--;
    }
    if (parentheses == 0 && i != q) {
      false_parentheses = 1;
    }
  }

  if (parentheses != 0) {
    illegal = 1;
    false_parentheses = 1;
  }

  return false_parentheses == 0;
}

static bool check_op(int type) {
  for (int i=0; i<NR_REGEX; i++) {
    if (rules[i].token_type == TK_NUM) {
      continue;
    }
    else if (rules[i].token_type == TK_HEX) {
      continue;
    }
    else if (rules[i].token_type == TK_REG) {
      continue;
    }
    else if (rules[i].token_type == '(') {
      continue;
    }
    else if (rules[i].token_type == ')') {
      continue;
    }
    else if (rules[i].token_type == TK_NOTYPE) {
      continue;
    }
    else if (rules[i].token_type == type) {
      return true;
    }
  }

  return false;
}

static int op_priority(int type) {
  assert(check_op(type) == true);

  switch (type) {
    case TK_DEREF: return 3;
    case '*': return 2;
    case '/': return 2;
    case '+': return 1;
    case '-': return 1;
    case TK_EQ: return 0;
    case TK_NEQ: return 0;
    case TK_AND: return 0;
    default: assert(0);
  }
}

static int cmp_op(int type1, int type2) {
  assert(check_op(type1) == true);
  assert(check_op(type2) == true);

  return op_priority(type1) - op_priority(type2);
}

static word_t eval(int p, int q) {
  if (p > q) {
    /* Bad expression */
    illegal = 1;
    return -1;
  }
  else if (p == q) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    if (tokens[p].type != TK_NUM) {
      illegal = 1;
      return -1;
    }
    return atoi(tokens[p].str);
  }
  else if (check_parentheses(p, q) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(p + 1, q - 1);
  }
  else {
    if (illegal == 1) {
      return -1;
    }
    /* We should do more things here. */
    int parentheses = 0;
    int op = 0;
    int position = 0;
    for(int i = p; i <= q; i++) {
      if (tokens[i].type == '(') {
        parentheses++;
      }
      else if (tokens[i].type == ')') {
        parentheses--;
      }
      else if (parentheses == 0) {
        if (check_op(tokens[i].type) == true) {
          if (op == 0) {
            op = tokens[i].type;
            position = i;
          }
          else if (cmp_op(op, tokens[i].type) >= 0) {
            op = tokens[i].type;
            position = i;
          }
        }
      }
    }
    uint32_t val1 = eval(p, position - 1);
    uint32_t val2 = eval(position + 1, q);
    switch (op) {
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case TK_EQ: return val1 == val2;
      default: assert(0);
    }
  }
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  /* TODO: Insert codes to evaluate the expression. */
  illegal = 0;
  int result = eval(0, nr_token - 1);

  if (illegal == 1) {
    *success = false;
    return 0;
  }

  *success = true;
  return result;
}
