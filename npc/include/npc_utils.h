#ifndef __NPC_UTILS_H__
#define __NPC_UTILS_H__

#include "npc_common.h"

enum { NPC_RUNNING, NPC_STOP, NPC_END, NPC_ABORT, NPC_QUIT };

typedef struct {
    int state;
    addr_t halt_pc;
    uint32_t halt_ret;
} NPCState;

extern NPCState npc_state;

#endif