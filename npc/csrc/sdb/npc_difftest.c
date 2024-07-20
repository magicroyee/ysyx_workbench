#include <dlfcn.h>
#include "debug.h"
#include "sdb/npc_difftest.h"

void (*ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction) = NULL;
// typedef void (*type_ref_difftest_memcpy)(paddr_t addr, void *buf, size_t n, bool direction);
void (*ref_difftest_regcpy)(void *dut, bool direction) = NULL;
void (*ref_difftest_exec)(uint64_t n) = NULL;
// void (*ref_difftest_raise_intr)(uint64_t NO) = NULL;

CPU_state cpu;

void init_difftest(char *ref_so_file, long img_size, int port) {
    assert(ref_so_file != NULL);

    void *handle;
    handle = dlopen(ref_so_file, RTLD_LAZY);
    assert(handle);

    ref_difftest_memcpy = dlsym(handle, "difftest_memcpy");
    assert(ref_difftest_memcpy);

    ref_difftest_regcpy = dlsym(handle, "difftest_regcpy");
    assert(ref_difftest_regcpy);

    ref_difftest_exec = dlsym(handle, "difftest_exec");
    assert(ref_difftest_exec);

    // ref_difftest_raise_intr = dlsym(handle, "difftest_raise_intr");
    // assert(ref_difftest_raise_intr);
    isa_reg_read();

    ref_difftest_memcpy(RESET_VECTOR, guest_to_host(RESET_VECTOR), img_size, DIFFTEST_TO_REF);
    ref_difftest_regcpy(&cpu, DIFFTEST_TO_REF);
}

void checkregs(CPU_state *ref, vaddr_t pc) {
    if (!isa_difftest_checkregs(ref, pc)) {
        npc_state.state = NPC_ABORT;
        npc_state.halt_pc = pc;
        isa_reg_display();
    }
}

void difftest_step(vaddr_t pc, vaddr_t npc) {
    CPU_state ref_r;
    
    isa_reg_read();
    
    ref_difftest_exec(1);
    ref_difftest_regcpy(&ref_r, DIFFTEST_TO_DUT);

    checkregs(&ref_r, npc);
}