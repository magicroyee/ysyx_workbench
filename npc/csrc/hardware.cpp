#include "hardware.h"
#include "npc_init.h"

void step_and_dump_wave()
{
    top->eval();
    contextp->timeInc(1);
    tfp->dump(contextp->time());
}

void single_cycle() {
    top->clk = 0;
    step_and_dump_wave();
    top->clk = 1;
    step_and_dump_wave();
}

void reset(int n) {
    top->rstn = 0;
    while (n-- > 0)
        single_cycle();
    top->rstn = 1;
}

const char *regs[] = {
  "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

// void isa_reg_display() {
//     printf("%-3s: 0x%08x\n", "pc", cpu.pc);
//   for (int i = 0; i < 32; i++) {
//     printf("%-3s: 0x%08x", regs[i], gpr(i));
//     if (i % 4 == 3) printf("\n");
//     else printf("\t");
//   }
// }

word_t isa_reg_str2val(const char *s, bool *success) {
  if (strcmp(s, "pc") == 0) {
    *success = true;
    return CPU_PC;
  }
  for (int i = 0; i < 32; i++) {
    if (strcmp(regs[i], s) == 0) {
      *success = true;
      return gpr(i);
    }
  }
  *success = false;
  return 0;
}