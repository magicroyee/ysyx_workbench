#include "npc_memory.h"

char mem[MEMORY_SIZE];

word_t mem_read(addr_t addr, int len) {
    switch (len)
    {
        case 1: return *(uint8_t *)(mem + addr);
        case 2: return *(uint16_t *)(mem + addr);
        case 4: return *(uint32_t *)(mem + addr);
        default: printf("not valid len.\n"); return 0;
    }
}

void mem_write(addr_t addr, word_t data, int len) {
    switch (len)
    {
        case 1: *(uint8_t *)(mem + addr) = data; break;
        case 2: *(uint16_t *)(mem + addr) = data; break;
        case 4: *(uint32_t *)(mem + addr) = data; break;
        default: printf("not valid len.\n"); break;
    }
}

word_t vaddr_read(addr_t addr, int len) {
    addr_t maddr = addr - MEM_BASE;
    if (addr >= 0 && addr < MEMORY_SIZE) {
        return mem_read(maddr, len);
    }
    else {
        return 0;
    }
}