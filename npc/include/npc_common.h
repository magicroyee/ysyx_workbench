#ifndef __NPC_COMMON__H__
#define __NPC_COMMON__H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_SIZE 0x8000000
#define LOG_BUF_LEN 128

#define __MIN(a, b) ((a) < (b) ? (a) : (b))

typedef uint32_t word_t;
typedef word_t addr_t;
typedef word_t vaddr_t;
typedef word_t paddr_t;

#endif