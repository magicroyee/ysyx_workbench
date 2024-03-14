#ifndef __NPC_MEMORY__H__
#define __NPC_MEMORY__H__

#include "npc_common.h"

word_t mem_read(addr_t addr, int len);
void mem_write(addr_t addr, word_t data, int len);

#endif