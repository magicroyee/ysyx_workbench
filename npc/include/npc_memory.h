#ifndef __NPC_MEMORY__H__
#define __NPC_MEMORY__H__

#include "npc_common.h"

#define MEM_BASE 0x80000000
#define RESET_VECTOR MEM_BASE

uint8_t *guest_to_host(vaddr_t addr);

word_t vaddr_read(addr_t addr, int len);
word_t mem_read(addr_t addr, int len);
void mem_write(addr_t addr, word_t data, int len);

#endif