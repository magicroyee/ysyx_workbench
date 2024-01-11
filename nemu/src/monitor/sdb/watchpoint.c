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

#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
    wp_pool[i].expr = NULL;
    wp_pool[i].eval = 0;
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
void insert_wp(WP **_head, WP *wp) 
{
  if (*_head == NULL) {
    *_head = wp;
    wp->next = NULL;
    return ;
  }
  WP *p = *_head;
  if (wp->NO < p->NO) {
    wp->next = p;
    *_head = wp;
    return ;
  }
  while (p->next != NULL) {
    if (wp->NO < p->next->NO) {
      wp->next = p->next;
      p->next = wp;
      return ;
    }
    p = p->next;
  }
  p->next = wp;
  wp->next = NULL;
}

WP *extract_wp(WP **_head, int NO)
{
  if (*_head == NULL) {
    printf("No watchpoint in heads!\n");
    assert(0);
  }
  WP *p = *_head;
  if (p->NO == NO) {
    *_head = (*_head)->next;
    p->next = NULL;
    return p;
  }
  while (p->next != NULL) {
    if (p->next->NO == NO) {
      WP *q = p->next;
      p->next = q->next;
      q->next = NULL;
      return q;
    }
    p = p->next;
  }
  printf("No such watchpoint!\n");
  assert(0);
}

WP* new_wp(char *expr) {
  if (free_ == NULL) {
    printf("No more watchpoint!\n");
    assert(0);
  }
  WP *wp = extract_wp(&free_, free_->NO);
  wp->expr = malloc(strlen(expr) + 1);
  if(!wp->expr) {
    printf("malloc failed!\n");
    assert(0);
  }
  strcpy(wp->expr, expr);
  insert_wp(&head, wp);
  return wp;
}

void free_wp(int NO)
{
  WP *wp = extract_wp(&head, NO);
  free(wp->expr);
  wp->expr = NULL;
  wp->eval = 0;
  insert_wp(&free_, wp);
}

void print_wp()
{
  if (head == NULL) {
    printf("No watchpoint!\n");
    return ;
  }
  WP *p = head;
  while (p != NULL) {
    printf("Watchpoint %d: %s\n", p->NO, p->expr);
    p = p->next;
  }
}

int diff_wp()
{
  if (head == NULL) {
    return 0;
  }
  WP *p = head;
  bool success = true;
  int diff_flag = 0;
  while (p != NULL) {
    uint32_t new_eval = expr(p->expr, &success);
    if (success == false) {
      printf("Invalid watch point expression!\n");
      assert(0);
    }
    if (new_eval != p->eval) {
      printf("Watchpoint %d: %s\n", p->NO, p->expr);
      printf("Old value = %u\n", p->eval);
      printf("New value = %u\n", new_eval);
      p->eval = new_eval;
      diff_flag++;
    }
    p = p->next;
  }
  return diff_flag;
}
