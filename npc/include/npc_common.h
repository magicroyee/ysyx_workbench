#ifndef __NPC_COMMON__H__
#define __NPC_COMMON__H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "npc_config.h"

// #define MEMORY_SIZE 0x8000000
#define LOG_BUF_LEN 128
#define CONFIG_MBASE 0x80000000
#define CONFIG_PC_RESET_OFFSET 0x0
#define CONFIG_MSIZE 0x8000000

#define CONFIG_I8042_DATA_MMIO 0xa0000060
#define CONFIG_SERIAL_MMIO 0xa00003f8
#define CONFIG_RTC_MMIO 0xa0000048
#define CONFIG_SDCARD_CTL_MMIO 0xa3000000
#define CONFIG_AUDIO_CTL_MMIO 0xa0000200
#define CONFIG_SB_ADDR 0xa1200000
#define CONFIG_SB_SIZE 0x10000
#define CONFIG_VGA_CTL_MMIO 0xa0000100
#define CONFIG_FB_ADDR 0xa1000000
#define CONFIG_VGA_SHOW_SCREEN 1
#define CONFIG_VGA_SIZE_400x300 1
#define CONFIG_SDCARD_IMG_PATH ""

#define __MIN(a, b) ((a) < (b) ? (a) : (b))

typedef uint32_t word_t;
typedef word_t addr_t;
typedef word_t vaddr_t;
typedef word_t paddr_t;
typedef uint16_t ioaddr_t;

#include "debug.h"

#endif