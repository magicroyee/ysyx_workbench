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

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = (unsigned int)(%s); "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
static int ind = 0;

static inline uint32_t choose(uint32_t n) {
  return rand() % n;
}

static inline void gen(char c) {
  buf[ind++] = c;
  buf[ind] = '\0';
}

static inline void gen_num() {
  // choose to gen dec num or hex num
  if (choose(2) == 0) {
    gen('0');
    gen('x');
    for (int i=0; i < 8; i++) {
      gen(choose(16) < 10 ? choose(10) + '0' : choose(6) + 'a');
    }
    gen('u');
    return;
  }
  uint32_t n = choose(10);
  if (n == 0) {
    gen('0');
    gen('u');
    return;
  }
  for (int i=0; i < n; i++) {
    if (i == 0) {
      gen(choose(9) + '1');
    } else {
      gen(choose(10) + '0');
    }
  }
  gen('u');
}

static inline void gen_rand_op() {
  switch (choose(7)) {
    case 0: gen('+'); break;
    case 1: gen('-'); break;
    case 2: gen('*'); break;
    case 3: gen('/'); break;
    case 4: gen('='); gen('='); break;
    case 5: gen('!'); gen('='); break;
    case 6: gen('&'); gen('&'); break;
  }
}

static void gen_rand_expr() {
  if (ind >= 65536/2) {
    gen_num();
    return;
  }
switch (choose(4)) {
    case 0: gen_num(); break;
    case 1: gen('('); gen_rand_expr(); gen(')'); break;
    case 2: gen(' '); gen_rand_expr(); break;
    default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    ind = 0;
    gen_rand_expr();
    // sprintf(buf, "4294967295+(2*4294967295)");

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc -Werror=div-by-zero /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    ret = fscanf(fp, "%d", &result);
    pclose(fp);

    if (ret != 1) continue;

    printf("%u %s\n", result, buf);
  }
  return 0;
}
