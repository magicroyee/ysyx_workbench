#include "npc_common.h"
#include "npc_init.h"

extern void reg_value(const svLogicVecVal* reg_num, svLogicVecVal* value);

void single_cycle();
void reset(int n);
void step_and_dump_wave();