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

bool break_flag = 0;
word_t npc_ret = -1;

extern char mem[MEMORY_SIZE];

void ebreak() {
    printf("ebreak\n");
    npc_state.state = NPC_END;
    int tmp = 10;
    reg_value((const svLogicVecVal*)&tmp, (svLogicVecVal*)&npc_ret);
}

int main(int argc, char** argv)
{
    u_int32_t mem_rd = 0;
    u_int32_t mem_raddr = 0;

    init_monitor(argc, argv);

    reset(10);
    sdb_mainloop();

    if (npc_ret == 0) {
        printf("NPC \33[1;32mHIT GOOD TRAP\33[0m.\n");
    }
    else {
        printf("NPC \33[1;31mHIT BAD TRAP\33[0m with ret %d.\n", npc_ret);
    }

    release_monitor();

    return 0;
}