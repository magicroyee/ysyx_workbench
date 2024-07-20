#include "npc_utils.h"
#include "npc_common.h"
#include "npc_memory.h"
#include "hardware.h"

#define DIFFTEST_TO_DUT 0
#define DIFFTEST_TO_REF 1

void init_difftest(char *ref_so_file, long img_size, int port);
void checkregs(CPU_state *ref, vaddr_t pc);
void difftest_step(vaddr_t pc, vaddr_t npc);
