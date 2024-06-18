#ifndef __NPC_FTRACE_H__
#define __NPC_FTRACE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <elf.h>
#include "npc_common.h"

#define FUNC_TAB_SIZE 100

typedef struct {
    int size;
    Elf32_Sym tab[FUNC_TAB_SIZE];
} func_tab;

int npc_ftrace_init(const char *elfname);
void npc_ftrace_release();
const char *npc_ftrace_lookup(uint32_t addr);
void npc_ftrace(word_t addr, word_t pc, int rd, int rs1);

#endif