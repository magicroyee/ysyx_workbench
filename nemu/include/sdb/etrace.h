#ifndef __ETRACE_H__
#define __ETRACE_H__

#include <stdio.h>
#include "common.h"

void etrace_ecall(word_t NO, vaddr_t epc);
void etrace_mret(vaddr_t epc);

#endif