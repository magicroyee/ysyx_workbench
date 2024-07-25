#include "npc_memory.h"

word_t mem_read(addr_t addr, int len) {
    return vaddr_read(addr+RESET_VECTOR, len);
}

void mem_write(addr_t addr, word_t data, int len) {
    vaddr_write(addr+RESET_VECTOR, len, data);
}
