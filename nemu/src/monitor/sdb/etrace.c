#include "sdb/etrace.h"

void etrace_ecall(word_t NO, vaddr_t epc) {
    Log("ecall: NO = %d, epc = 0x%08x", NO, epc);
}

void etrace_mret(vaddr_t epc) {
    Log("mret: epc = 0x%08x", epc);
}
