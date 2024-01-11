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

typedef struct watchpoint {
  int NO;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */
  char *expr;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
void insert_wp(WP *head, WP *wp) 
{
  if (head == NULL) {
    head = wp;
    return ;
  }
  wp->next = head;
  head = wp;
}

WP *extract_wp(WP *head, WP *wp)
{
  if (head == NULL) {
    printf("No watchpoint in heads!\n");
    assert(0);
  }
  WP *p = head;
  if (p == wp) {
    head = head->next;
    p->next = NULL;
    return p;
  }
  while (p->next != NULL) {
    if (p->next == wp) {
      WP *q = p->next;
      p->next = p->next->next;
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
  WP *wp = extract_wp(free_, free_);
  wp->expr = malloc(strlen(expr) + 1);
  if(!wp->expr) {
    printf("malloc failed!\n");
    assert(0);
  }
  strcpy(wp->expr, expr);
  insert_wp(head, wp);
  return wp;
}

void free_wp(WP *wp)
{
  if (wp == NULL) {
    printf("Wp should not be NULL!\n");
    assert(0);
  }
  WP *p = extract_wp(head, wp);
  free(p->expr);
  insert_wp(free_, p);
}
