#ifndef __FTRACE_H__
#define __FTRACE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <elf.h>
#include "common.h"

#define FUNC_TAB_SIZE 100

typedef struct {
    int size;
    Elf32_Sym tab[FUNC_TAB_SIZE];
} func_tab;

int ftrace_init(const char *elfname);
void ftrace_release();
const char *ftrace_lookup(uint32_t addr);
void ftrace(word_t addr, word_t pc);

#endif