#include <npc_cpu.h>
#include "npc_init.h"
#include "npc_memory.h"
#include "hardware.h"

u_int32_t mem_rd = 0;
u_int32_t mem_raddr = 0;

static void exec_once() {
    // top->eval();
    // mem_rd = top->mem_rd;
    // if (mem_rd) {
    //     mem_raddr = top->mem_raddr - 0x80000000;
    //     top->mem_rdata = mem_read(mem_raddr, 4);
    // }
    // else {
    //     top->mem_rdata = 0;
    // }
    // single_cycle();
    // nvboard_update();
    if (npc_state.state != NPC_RUNNING) {
        return;
    }
    while (!top->mem_rd) {
        top->eval();
        single_cycle();
    }
    while (top->mem_rd)
    {
        top->eval();
        mem_raddr = top->mem_raddr - 0x80000000;
        top->mem_rdata = mem_read(mem_raddr, 4);
        single_cycle();
    }
    while (!top->mem_rd) {
        top->eval();
        single_cycle();
    }
}

static void execute(uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        exec_once();
        if (npc_state.state != NPC_RUNNING) {
            break;
        }
    }
}

void cpu_exec(uint32_t n) {
    switch (npc_state.state) {
        case NPC_END:
        case NPC_ABORT:
            printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
            return;
        default:
            npc_state.state = NPC_RUNNING;
    }

    execute(n);

    switch (npc_state.state) {
        case NPC_RUNNING:
            npc_state.state = NPC_STOP;
            break;
        case NPC_END:
        case NPC_ABORT:
            printf("Program execution has ended.\n");
        case NPC_STOP:
            break;
    }
}