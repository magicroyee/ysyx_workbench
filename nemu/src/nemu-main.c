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

#include <common.h>
#include "./monitor/sdb/sdb.h"

void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

//   /* Start engine. */
//   engine_start();

  printf("hex 0x10 = %ld\n", strtol("0x10", NULL, 16));

  // open a file for reading
  // FILE *fp = fopen("/home/zhu/workspace/ysyx-workbench/nemu/tools/gen-expr/input", "r");
  // assert(fp != NULL);
  
  // // read a line
  // char *line = NULL;
  // size_t len = 0;
  // ssize_t read;
  // uint32_t res;
  // char *res_ptr;
  // char *eval_ptr;
  // bool success;

  // while ((read = getline(&line, &len, fp)) != -1) {
  //   res_ptr = strtok(line, " ");
  //   eval_ptr = strtok(NULL, "\n");
  //   res = expr(eval_ptr, &success);
  //   assert(success);
  //   assert(res == atoi(res_ptr));
  // }

  // // close the file
  // fclose(fp);

  return is_exit_status_bad();
}
