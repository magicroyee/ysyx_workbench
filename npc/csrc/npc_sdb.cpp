#include <readline/readline.h>
#include <readline/history.h>
#include "npc_init.h"
#include "npc_sdb.h"
#include "npc_cpu.h"
#include "npc_memory.h"
#include "npc_config.h"
#include "npc_ftrace.h"
#include "hardware.h"

NPCState npc_state;
static const char * elf_file = NULL;
bool is_batch_mode = false;

word_t expr(char *e, bool *success);

void sdb_set_elfname(const char *elfname)
{
    elf_file = elfname;
}

void sdb_set_batch_mode() {
    is_batch_mode = true;
}

void sdb_init()
{
    IFDEF(FTRACE, if(elf_file) npc_ftrace_init(elf_file));
}

void sdb_release()
{
    IFDEF(FTRACE, npc_ftrace_release());
}

static int cmd_help(char *args);

static int cmd_c(char *args) {
    cpu_exec(-1);
    if (npc_state.state == NPC_STOP) {
        // printf("Program stop at pc: 0x%08x: 0x%08x\n", npc_state.halt_pc, vaddr_read(npc_state.halt_pc, 4));
        printf("Program stop at pc: 0x%08x\n", npc_state.halt_pc);
    }
    return 0;
}

static int cmd_q(char *args) {
    npc_state.state = NPC_QUIT;
    return -1;
}

static int cmd_si(char *args) {
    char *arg = strtok(NULL, " ");
    int n = 1;
    if (arg != NULL) {
        sscanf(arg, "%d", &n);
    }
    cpu_exec(n);
    if (npc_state.state == NPC_STOP) {
        printf("Program stop at pc: 0x%08x.\n", top->rootp->top__DOT__cpu_core__DOT__pc);
    }
    return 0;
}

static int cmd_x(char *args) {
    char *arg = strtok(NULL, " ");
    if (arg == NULL) {
        printf("Please specify the length!\n");
        return 0;
    }
    int n;
    sscanf(arg, "%d", &n);
    arg = strtok(NULL, " ");
    if (arg == NULL) {
        printf("Please specify the address!\n");
        return 0;
    }
    vaddr_t addr;
    bool success;
    addr = expr(arg, &success);
    if (success == false) {
        printf("Invalid expression!\n");
        return 0;
    }
    printf("addr: 0x%08x\n", addr);
    // sscanf(arg, "%x", &addr);
    for (int i = 0; i < n; i++) {
        printf("0x%08x: 0x%08x\n", addr + i * 4, vaddr_read(addr + i * 4, 4));
    }
    return 0;
}

static int cmd_info(char *args) {
    char *arg = strtok(NULL, " ");
    if (arg == NULL) {
        printf("Please specify the subcommand!\n");
        return 0;
    }
    if (strcmp(arg, "r") == 0) {
        isa_reg_display();
    }
    // else if (strcmp(arg, "w") == 0) {
    //     print_wp();
    // }
    // else if (strcmp(arg, "i") == 0) {
    //     IFDEF(CONFIG_ITRACE, rb_print(&irb));
    // }
    // else if (strcmp(arg, "m") == 0) {
    //     IFDEF(CONFIG_MTRACE, rb_print(&mtrace));
    // }
    else {
        printf("Unknown subcommand '%s'\n", arg);
    }
    return 0;
}

static struct {
    const char *name;
    const char *description;
    int (*handler) (char *);
} cmd_table [] = {
    { "help", "Display information about all supported commands", cmd_help },
    { "c", "Continue the execution of the program", cmd_c },
    { "q", "Exit NEMU", cmd_q },

    /* TODO: Add more commands */
    { "si", "Single step execution", cmd_si },
    { "info", "Print the status of registers or watchpoints", cmd_info },
    { "x", "Scan the memory", cmd_x },
    // { "p", "Print the result of expression", cmd_p },
    // { "w", "Set a watchpoint", cmd_w },
    // { "d", "Delete a watchpoint", cmd_d },
};

#define ARRLEN(arr) (int)(sizeof(arr) / sizeof(arr[0]))
#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
    /* extract the first argument */
    char *arg = strtok(NULL, " ");
    int i;

    if (arg == NULL) {
        /* no argument given */
        for (i = 0; i < NR_CMD; i ++) {
            printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        }
    }
    else {
        for (i = 0; i < NR_CMD; i ++) {
            if (strcmp(arg, cmd_table[i].name) == 0) {
                printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
                return 0;
            }
        }
        printf("Unknown command '%s'\n", arg);
    }
    return 0;
}

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
    static char *line_read = NULL;

    if (line_read) {
        free(line_read);
        line_read = NULL;
    }

    line_read = readline("(nemu) ");

    if (line_read && *line_read) {
        add_history(line_read);
    }

    return line_read;
}

void sdb_mainloop()
{
    if (is_batch_mode) {
        cpu_exec(-1);
        return;
    }
    for (char *str; (str = rl_gets()) != NULL; ) {
        char *str_end = str + strlen(str);

        /* extract the first token as the command */
        char *cmd = strtok(str, " ");
        if (cmd == NULL) { continue; }

        /* treat the remaining string as the arguments,
         * which may need further parsing
         */
        char *args = cmd + strlen(cmd) + 1;
        if (args >= str_end) {
            args = NULL;
        }

        int i;
        for (i = 0; i < NR_CMD; i ++) {
            if (strcmp(cmd, cmd_table[i].name) == 0) {
                if (cmd_table[i].handler(args) < 0) { 
                    return; 
                }
                break;
            }
        }

        if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
    }
}