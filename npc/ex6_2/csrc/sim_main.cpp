#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

u_int8_t din[] = {0x00, 0x01, 0x11, 0x55, 0x99, 0xff};

VerilatedContext *contextp = NULL;
VerilatedVcdC *tfp = NULL;
static Vtop *top = NULL;

void step_and_dump_wave()
{
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void single_cycle()
{
    top->clk = 0;
    step_and_dump_wave();
    top->clk = 1;
    step_and_dump_wave();
}

void reset(int n)
{
    top->rstn = 0;
    while (n-- > 0)
        single_cycle();
    top->rstn = 1;
}

int main(int argc, char **argv)
{
    contextp = new VerilatedContext;
    tfp = new VerilatedVcdC;
    top = new Vtop{contextp};
    contextp->commandArgs(argc, argv);

    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("./sim/wave.vcd");

    reset(10);

    while (!contextp->gotFinish())
    {
        // printf("x = %d\n", top->x);
        // single_cycle();
        for (int i=0; i<8; i++){
            for (int j=0; j<sizeof(din); j++){
                top->din = din[j];
                top->shamt = i;
                top->lr = 0;
                top->al = 0;
                single_cycle();
                printf("shamt = %d, din = %d, dout = %d\n", i, din[j], top->dout);
                top->lr = 0;
                top->al = 1;
                single_cycle();
                printf("shamt = %d, din = %d, dout = %d\n", i, din[j], top->dout);
                top->lr = 1;
                top->al = 0;
                single_cycle();
                printf("shamt = %d, din = %d, dout = %d\n", i, din[j], top->dout);
                top->lr = 1;
                top->al = 1;
                single_cycle();
                printf("shamt = %d, din = %d, dout = %d\n", i, din[j], top->dout);
            }
        }
    }

    delete top;
    tfp->close();
    delete contextp;
    return 0;
}