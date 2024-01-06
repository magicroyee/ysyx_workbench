#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <nvboard.h>
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

static TOP_NAME dut;

VerilatedContext *contextp = NULL;
VerilatedVcdC *tfp = NULL;
static Vtop *top = NULL;

void step_and_dump_wave()
{
    top->eval();
    contextp->timeInc(100);
    tfp->dump(contextp->time());
};

void nvboard_bind_all_pins(Vtop *top);

static void single_cycle() {
    dut.clk = 0; dut.eval();
    dut.clk = 1; dut.eval();
}

static void reset(int n) {
    dut.rstn = 0;
    while (n -- > 0) single_cycle();
    dut.rstn = 1;
}

int main(int argc, char** argv)
{
    contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    top = new Vtop{contextp};
    contextp->traceEverOn(true);

    tfp = new VerilatedVcdC;
    top->trace(tfp, 0);
    tfp->open("./build/wave.vcd");

    nvboard_bind_all_pins(&dut);
    nvboard_init();

    reset(10);

    dut.eval();
    while(1) {
        // dut.eval();
        nvboard_update();
        single_cycle();
        step_and_dump_wave();
    }

    nvboard_quit();

    delete top;
    tfp->close();
    delete contextp;
    return 0;
}