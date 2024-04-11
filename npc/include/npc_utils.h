#ifndef __NPC_UTILS_H__
#define __NPC_UTILS_H__

#include "npc_common.h"

enum { NEMU_RUNNING, NEMU_STOP, NEMU_END, NEMU_ABORT, NEMU_QUIT };

typedef struct {
    int state;
    addr_t halt_pc;
    uint32_t halt_ret;
} NPCState;

extern NPCState npc_state;

#endif