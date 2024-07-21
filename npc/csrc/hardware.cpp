#include "hardware.h"
#include "npc_init.h"
#include "npc_memory.h"

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

void isa_reg_display() {
    printf("%-3s: 0x%08x\n", "pc", CPU_PC);
    for (int i = 0; i < 32; i++) {
        printf("%-3s: 0x%08x", regs[i], GPR(i));
        if (i % 4 == 3) printf("\n");
        else printf("\t");
    }
}

void cpu_reg_display(CPU_state *cpu) {
    printf("%-3s: 0x%08x\n", "pc", cpu->pc);
    for (int i = 0; i < 32; i++) {
        printf("%-3s: 0x%08x", regs[i], cpu->gpr[i]);
        if (i % 4 == 3) printf("\n");
        else printf("\t");
    }
}

word_t isa_reg_str2val(const char *s, bool *success) {
    if (strcmp(s, "pc") == 0) {
        *success = true;
        return CPU_PC;
    }
    for (int i = 0; i < 32; i++) {
        if (strcmp(regs[i], s) == 0) {
        *success = true;
        return GPR(i);
        }
    }
    *success = false;
    return 0;
}

u_int32_t mem_rd = 0;
u_int32_t mem_raddr = 0;
u_int32_t mem_wr = 0;
u_int32_t mem_wdata = 0;
u_int32_t mem_wbit_en = 0;

void isa_exec_once()
{
    // while (!top->mem_rd) {
    //     top->eval();
    //     single_cycle();
    //     EXEC_CHECK_END;
    // }
    // while (top->mem_rd)
    // {
    //     top->eval();
    //     mem_raddr = top->mem_raddr - 0x80000000;
    //     single_cycle();
    //     top->mem_rdata = mem_read(mem_raddr, 4);
    //     EXEC_CHECK_END;
    // }
    // while (!top->mem_rd) {
    //     top->eval();
    //     single_cycle();
    //     EXEC_CHECK_END;
    // }
    while (!(NPC_STATE == 5)) {
        top->eval();
        mem_rd = top->mem_rd;
        mem_raddr = top->mem_raddr - 0x80000000;
        mem_wr = top->mem_wr;
        mem_wdata = top->mem_wdata;
        mem_wbit_en = top->mem_wbit_en;
        single_cycle();
        if (mem_rd)
        {
            top->mem_rdata = mem_read(mem_raddr, 4);
        }
        if (mem_wr)
        {
            mem_write(mem_raddr, mem_wdata, mem_wbit_en);
            // printf("write mem: 0x%08x: 0x%08x\n", top->mem_raddr, top->mem_wdata);
        }
        EXEC_CHECK_END;
    }
    while (NPC_STATE == 5) {
        top->eval();
        mem_rd = top->mem_rd;
        mem_raddr = top->mem_raddr - 0x80000000;
        mem_wr = top->mem_wr;
        mem_wdata = top->mem_wdata;
        mem_wbit_en = top->mem_wbit_en;
        single_cycle();
        if (mem_rd)
        {
            top->mem_rdata = mem_read(mem_raddr, 4);
        }
        if (mem_wr)
        {
            mem_write(mem_raddr, mem_wdata, mem_wbit_en);
            // printf("write mem: 0x%08x: 0x%08x\n", top->mem_raddr, top->mem_wdata);
        }
        EXEC_CHECK_END;
    }
}

void isa_reg_read()
{
    for (int i = 0; i < 32; i++)
    {
        cpu.gpr[i] = GPR(i);
    }
    cpu.pc = CPU_PC;
}

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc)
{
    bool is_same = true;
    for (int i = 0; i < 32; i++)
    {
        if (ref_r->gpr[i] != cpu.gpr[i])
        {
            is_same = false;
            printf("reg[%d] is different! ref: 0x%08x, dut: 0x%08x\n", i, ref_r->gpr[i], GPR(i));
            goto err;
        }
    }
    if (ref_r->pc != cpu.pc)
    {
        is_same = false;
        printf("pc is different! ref: 0x%08x, dut: 0x%08x\n", ref_r->pc, CPU_PC);
    }
err:
    return is_same;
}
