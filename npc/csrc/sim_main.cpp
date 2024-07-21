#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <nvboard.h>
#include "npc_memory.h"
#include "npc_init.h"
#include "npc_sdb.h"
#include "hardware.h"

extern NPCState npc_state;
extern int jump_valid;
extern word_t npc_addr;
extern word_t npc_pc;
extern int npc_rd;
extern int npc_rs1;

bool break_flag = 0;
word_t npc_ret = -1;

extern char mem[MEMORY_SIZE];

void ebreak() {
    printf("ebreak\n");
    npc_state.state = NPC_END;
    int tmp = 10;
    reg_value((const svLogicVecVal*)&tmp, (svLogicVecVal*)&npc_ret);
}

void jump_en(int addr, int pc, int rd, int rs1) {
    // printf("jump_en\n");
    jump_valid = 1;
    npc_addr = addr;
    npc_pc = pc;
    npc_rd = rd;
    npc_rs1 = rs1;
}

int main(int argc, char** argv)
{
    u_int32_t mem_rd = 0;
    u_int32_t mem_raddr = 0;

    init_monitor(argc, argv);

    sdb_mainloop();

    if (npc_state.state == NPC_END && npc_ret == 0) {
        printf("NPC \33[1;32mHIT GOOD TRAP\33[0m.\n");
    }
    else {
        printf("NPC \33[1;31mHIT BAD TRAP\33[0m with ret %d.\n", npc_ret);
        return -1;
    }

    release_monitor();

    return 0;
}