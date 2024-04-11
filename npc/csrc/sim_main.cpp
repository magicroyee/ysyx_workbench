#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <nvboard.h>
#include "npc_memory.h"
#include "npc_init.h"

extern void reg_value(const svLogicVecVal* reg_num, svLogicVecVal* value);

bool break_flag = 0;
word_t npc_ret = -1;

extern char mem[MEMORY_SIZE];

void ebreak() {
    printf("ebreak\n");
    break_flag = 1;
    int tmp = 10;
    reg_value((const svLogicVecVal*)&tmp, (svLogicVecVal*)&npc_ret);
}


void nvboard_bind_all_pins(Vtop *top);

void step_and_dump_wave()
{
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

static void single_cycle() {
    top->clk = 0;
    step_and_dump_wave();
    top->clk = 1;
    step_and_dump_wave();
}

static void reset(int n) {
    top->rstn = 0;
    while (n-- > 0)
        single_cycle();
    top->rstn = 1;
}

int main(int argc, char** argv)
{


    u_int32_t mem_rd = 0;
    u_int32_t mem_raddr = 0;
    // nvboard_bind_all_pins(&dut);
    // nvboard_init();

    // if (argc > 1) {
    //     printf("Loading program from file %s\n", argv[1]);
    //     FILE *fp = fopen(argv[1], "r");
    //     if (fp == NULL) {
    //         printf("Failed to open file %s\n", argv[1]);
    //         return 1;
    //     }
    //     int i = 0;
    //     while (fscanf(fp, "%x", &mem[i]) != EOF) {
    //         i++;
    //     }
    //     fclose(fp);
    // }
    // else {
    //     printf("No program file specified, using default program.\n");
    // }

    init_monitor(argc, argv);

    reset(10);

    printf("Reset finished.\n");

    // dut.eval();
    while(1) {
        top->eval();
        mem_rd = top->mem_rd;
        if (mem_rd) {
            mem_raddr = top->mem_raddr - 0x80000000;
            top->mem_rdata = mem_read(mem_raddr, 4);
        }
        else {
            top->mem_rdata = 0;
        }
        single_cycle();
        // nvboard_update();
        if (mem_raddr > 20*4) {
            break;
        }
        if (break_flag) {
            break;
        }
    }

    if (npc_ret == 0) {
        printf("NPC \33[1;32mHIT GOOD TRAP\33[0m.\n");
    }
    else {
        printf("NPC \33[1;31mHIT BAD TRAP\33[0m with ret %d.\n", npc_ret);
    }

    release_monitor();

    return 0;
}