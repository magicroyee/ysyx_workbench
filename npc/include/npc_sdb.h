#ifndef __NPC_SDB_H__
#define __NPC_SDB_H__

#include "npc_common.h"
#include "npc_utils.h"

void sdb_init();
void sdb_mainloop();
void sdb_set_elfname(const char *elfname);
void sdb_release();

#endif
