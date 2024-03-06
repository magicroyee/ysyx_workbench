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

bool break_flag = 0;

void ebreak() {
    printf("ebreak\n");
    break_flag = 1;
}

int add(int a, int b) { return a+b; }

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

VerilatedContext *contextp = NULL;
VerilatedVcdC *tfp = NULL;
static Vtop *top = NULL;

u_int32_t mem[2048];

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

    mem[0] = inst("0000 0000 0001 00000 000 00001 0010011"); // addi x1, x0, 1
    mem[1] = inst("0000 0000 0010 00000 000 00010 0010011"); // addi x2, x0, 2
    mem[2] = inst("0000 0000 0011 00000 000 00011 0010011"); // addi x3, x0, 3
    mem[3] = inst("0000 0000 0100 00000 000 00100 0010011"); // addi x4, x0, 4
    mem[4] = inst("0000 0000 0101 00000 000 00101 0010011"); // addi x5, x0, 5
    mem[5] = inst("0000 0000 0110 00000 000 00110 0010011"); // addi x6, x0, 6
    mem[6] = inst("0000 0000 0111 00000 000 00111 0010011"); // addi x7, x0, 7
    mem[7] = inst("0000 0000 1000 00000 000 01000 0010011"); // addi x8, x0, 8
    mem[8] = inst("0000 0000 1001 00000 000 01001 0010011"); // addi x9, x0, 9
    mem[9] = inst("0000 0000 1010 00000 000 01010 0010011"); // addi x10, x0, 10
    mem[10] = inst("0000 0000 1011 00000 000 01011 0010011"); // addi x11, x0, 11
    mem[11] = inst("0000 0000 1100 00000 000 01100 0010011"); // addi x12, x0, 12
    mem[12] = inst("0000 0000 1101 00000 000 01101 0010011"); // addi x13, x0, 13
    mem[13] = inst("0000 0000 1110 00000 000 01110 0010011"); // addi x14, x0, 14
    mem[14] = inst("0000 0000 1111 00000 000 01111 0010011"); // addi x15, x0, 15
    mem[15] = inst("0000 0001 0000 00000 000 10000 0010011"); // addi x16, x0, 16

    // ebreak
    mem[16] = inst("0000 0000 0001 00000 000 00000 1110011");

    reset(10);

    printf("Reset finished.\n");

    // dut.eval();
    while(1) {
        top->eval();
        mem_rd = top->mem_rd;
        if (mem_rd) {
            mem_raddr = top->mem_raddr - 0x80000000;
            top->mem_rdata = mem[mem_raddr>>2];
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