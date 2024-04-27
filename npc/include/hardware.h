#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include "npc_common.h"
#include "npc_init.h"

#define CPU_PC top->rootp->top__DOT__cpu_core__DOT__pc
#define gpr(x) top->rootp->top__DOT__cpu_core__DOT__R[x]
#define INST top->rootp->top__DOT__cpu_core__DOT__instr

#define EXEC_CHECK_END { \
    if (npc_state.state != NPC_RUNNING) { \
        return; \
    } \
}

extern void reg_value(const svLogicVecVal* reg_num, svLogicVecVal* value);

void single_cycle();
void reset(int n);
void step_and_dump_wave();
void isa_reg_display();
word_t isa_reg_str2val(const char *s, bool *success);
void isa_exec_once();

#endif