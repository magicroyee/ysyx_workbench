#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

char op[] = {0, 1, 2, 3, 4, 5, 6, 7};
char a[] = {0, 1, 7, 8, 9, 15};
char b[] = {0, 1, 7, 8, 9, 15};

int main(int argc, char** argv)
{
    VerilatedContext* contextp = new VerilatedContext;
    contextp->commandArgs(argc, argv);
    Vtop* top = new Vtop{ contextp };

    VerilatedVcdC *tfp = new VerilatedVcdC;
    contextp->traceEverOn(true);
    top->trace(tfp, 0);
    tfp->open("./sim/wave.vcd");

    while (!contextp->gotFinish()) {
        for (int i=0; i<sizeof(op); i++) {
            for (int j=0; j<sizeof(a); j++) {
                for (int k=0; k<sizeof(b); k++) {
                    top->op = op[i];
                    top->a = a[j];
                    top->b = b[k];
                    top->eval();
                    printf("op = %d, a = %d, b = %d, y = %d\n", op[i], a[j], b[k], top->y);
                    tfp->dump(contextp->time());
                    contextp->timeInc(1);
                }
            }
        }
        // break;

    }
    delete top;
    tfp->close();
    delete contextp;
    return 0;
}