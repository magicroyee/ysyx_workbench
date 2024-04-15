#ifndef __NPC_INIT_H__
#define __NPC_INIT_H__

#include "npc_common.h"
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include "npc_utils.h"

extern VerilatedContext *contextp;
extern VerilatedVcdC *tfp;
extern Vtop *top;

int parse_args(int argc, char *argv[]);
int load_img();
void init_monitor(int argc, char *argv[]);
void release_monitor();

#endif