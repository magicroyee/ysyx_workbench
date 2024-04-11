#include <npc_cpu.h>

static void exec_once() {
}

static void execute(uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        exec_once();
    }
}

void cpu_exec(uint32_t n) {
    execute(n);
}