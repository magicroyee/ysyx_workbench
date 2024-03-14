#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <nvboard.h>
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "svdpi.h"
#include "Vtop__Dpi.h"
#include "npc_memory.h"
#include "npc_init.h"

bool break_flag = 0;
VerilatedContext *contextp = NULL;
VerilatedVcdC *tfp = NULL;
static Vtop *top = NULL;

extern char mem[MEMORY_SIZE];

void ebreak() {
    printf("ebreak\n");
    break_flag = 1;
}

static inline uint32_t inst(const char *str)
{
    uint32_t inst = 0;
    const char *p = str;
    while (*p != '\0') {
        if (*p == '0') {
            inst = (inst << 1) | 0;
        }
        else if (*p == '1') {
            inst = (inst << 1) | 1;
        }
        else if (*p == ' ') {
            // skip
        }
        else {
            assert(0);
        }
        p++;
    }
    return inst;
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
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop{contextp};
    contextp->commandArgs(argc, argv);

    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("./sim/wave.vcd");

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

    mem_write(0, inst("0000 0000 0001 00000 000 00001 0010011"), 4);
    mem_write(4, inst("0000 0000 0010 00000 000 00010 0010011"), 4);
    mem_write(8, inst("0000 0000 0011 00000 000 00011 0010011"), 4);
    mem_write(12, inst("0000 0000 0100 00000 000 00100 0010011"), 4);
    mem_write(16, inst("0000 0000 0101 00000 000 00101 0010011"), 4);
    mem_write(20, inst("0000 0000 0110 00000 000 00110 0010011"), 4);
    mem_write(24, inst("0000 0000 0111 00000 000 00111 0010011"), 4);
    mem_write(28, inst("0000 0000 1000 00000 000 01000 0010011"), 4);
    mem_write(32, inst("0000 0000 1001 00000 000 01001 0010011"), 4);
    mem_write(36, inst("0000 0000 1010 00000 000 01010 0010011"), 4);
    mem_write(40, inst("0000 0000 1011 00000 000 01011 0010011"), 4);
    mem_write(44, inst("0000 0000 1100 00000 000 01100 0010011"), 4);
    mem_write(48, inst("0000 0000 1101 00000 000 01101 0010011"), 4);
    mem_write(52, inst("0000 0000 1110 00000 000 01110 0010011"), 4);
    mem_write(56, inst("0000 0000 1111 00000 000 01111 0010011"), 4);
    mem_write(60, inst("0000 0001 0000 00000 000 10000 0010011"), 4);
    mem_write(64, inst("0000 0000 0001 00000 000 00000 1110011"), 4);

    parse_args(argc, argv);
    load_img();

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

    tfp->close();
    delete top;
    delete tfp;
    delete contextp;
    // nvboard_quit();

    return 0;
}