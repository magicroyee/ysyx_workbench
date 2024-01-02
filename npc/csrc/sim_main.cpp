#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vdswitch.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char** argv)
{
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vdswitch* top = new Vdswitch{ contextp };

    VerilatedVcdC *tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("wave.vcd");

    while (!contextp->gotFinish()) {
        int a = rand() & 1;
        int b = rand() & 1;
        top->a = a;
        top->b = b;
        top->eval();
        printf("a = %d, b = %d, f = %d\n", a, b, top->f);
        assert(top->f == (a ^ b));

        tfp->dump(contextp->time());
        contextp->timeInc(1);

    }
    delete top;
    tfp->close();
    delete contextp;
    return 0;
}