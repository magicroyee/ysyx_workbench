#include <npc_cpu.h>
#include "npc_init.h"
#include "npc_memory.h"
#include "hardware.h"

char log_buf[LOG_BUF_LEN];

static void trace()
{
    printf(log_buf);
}

static void exec_once() {
    uint32_t pc = CPU_PC;
    uint32_t instval = INST;
    char *p = log_buf;
    p += snprintf(p, sizeof(log_buf), "pc: 0x%08x:\n", CPU_PC);

    int ilen = 4;
    uint8_t *inst = (uint8_t *)&instval;
    for (int i = ilen - 1; i >= 0; i--) {
        p += snprintf(p, 4, " %02x", inst[i]);
    }

    int ilen_max = 4;
    int space_len = ilen_max - ilen;
    if (space_len < 0) {
        space_len = 0;
    }

    space_len = space_len * 3 + 1;
    memset(p, ' ', space_len);
    p += space_len;

    void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
    disassemble(p, log_buf + sizeof(log_buf) - p, pc, (uint8_t *)&instval, ilen);

    isa_exec_once();
}

static void execute(uint32_t n) {
    for (uint32_t i = 0; i < n; i++) {
        exec_once();
        trace();
        if (npc_state.state != NPC_RUNNING) {
            break;
        }
    }
}

void cpu_exec(uint32_t n) {
    switch (npc_state.state) {
        case NPC_END:
        case NPC_ABORT:
            printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
            return;
        default:
            npc_state.state = NPC_RUNNING;
    }

    execute(n);

    switch (npc_state.state) {
        case NPC_RUNNING:
            npc_state.state = NPC_STOP;
            break;
        case NPC_END:
        case NPC_ABORT:
            printf("Program execution has ended.\n");
        case NPC_STOP:
            break;
    }
}