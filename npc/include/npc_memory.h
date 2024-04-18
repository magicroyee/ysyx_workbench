#ifndef __NPC_MEMORY__H__
#define __NPC_MEMORY__H__

#include "npc_common.h"

#define MEM_BASE 0x80000000

word_t vaddr_read(addr_t addr, int len);
word_t mem_read(addr_t addr, int len);
void mem_write(addr_t addr, word_t data, int len);

#endif