#include <getopt.h>
#include <assert.h>
#include "npc_init.h"
#include "npc_config.h"
#include "npc_memory.h"
#include "npc_sdb.h"
#include "sdb/npc_difftest.h"

VerilatedContext *contextp = NULL;
IFDEF(CONFIG_WAVE, VerilatedVcdC *tfp = NULL);
Vtop *top = NULL;
char *img_file = NULL;

static char *diff_so_file = NULL;
static int difftest_port = 1234;

void init_disasm(const char *triple);
void init_device();

static inline uint32_t inst(const char *str)
{
    uint32_t inst = 0;
    const char *p = str;
    while (*p != '\0') {
        if (*p == '0') {
            inst = (inst << 1) | 0;
        }
        else if (*p == '1') {
            inst = (inst << 1) | 1;
        }
        else if (*p == ' ') {
            // skip
        }
        else {
            assert(0);
        }
        p++;
    }
    return inst;
}

int parse_args(int argc, char *argv[]) {
    const struct option table[] = {
        {"batch"    , no_argument      , NULL, 'b'},
        // {"log"      , required_argument, NULL, 'l'},
        {"diff"     , required_argument, NULL, 'd'},
        {"port"     , required_argument, NULL, 'p'},
        {"help"     , no_argument      , NULL, 'h'},
        {"elf"      , required_argument, NULL, 'e'},
        {0          , 0                , NULL,  0 },
    };
    int o;
    while ( (o = getopt_long(argc, argv, "-bhl:d:p:e:", table, NULL)) != -1) {
        switch (o) {
        case 'b': sdb_set_batch_mode(); break;
        case 'p': sscanf(optarg, "%d", &difftest_port); break;
        // case 'l': log_file = optarg; break;
        case 'd': diff_so_file = optarg; break;
        case 'e': sdb_set_elfname(optarg); break;
        case 1: img_file = optarg; return 0;
        default:
            printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
            printf("\t-b,--batch              run with batch mode\n");
            // printf("\t-l,--log=FILE           output log to FILE\n");
            printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
            printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
            printf("\t-e,--elf=FILE           specify the ELF file\n");
            printf("\n");
            exit(0);
        }
    }
    return 0;
}

static void init_mem()
{
    mem_write(0, inst("0000 0000 0001 00000 000 00001 0010011"), 4);
    mem_write(4, inst("0000 0000 0010 00000 000 00010 0010011"), 4);
    mem_write(8, inst("0000 0000 0011 00000 000 00011 0010011"), 4);
    mem_write(12, inst("0000 0000 0100 00000 000 00100 0010011"), 4);
    mem_write(16, inst("0000 0000 0101 00000 000 00101 0010011"), 4);
    mem_write(20, inst("0000 0000 0110 00000 000 00110 0010011"), 4);
    mem_write(24, inst("0000 0000 0111 00000 000 00111 0010011"), 4);
    mem_write(28, inst("0000 0000 1000 00000 000 01000 0010011"), 4);
    mem_write(32, inst("0000 0000 1001 00000 000 01001 0010011"), 4);
    mem_write(36, inst("0000 0000 1010 00000 000 01010 0010011"), 4);
    mem_write(40, inst("0000 0000 1011 00000 000 01011 0010011"), 4);
    mem_write(44, inst("0000 0000 1100 00000 000 01100 0010011"), 4);
    mem_write(48, inst("0000 0000 1101 00000 000 01101 0010011"), 4);
    mem_write(52, inst("0000 0000 1110 00000 000 01110 0010011"), 4);
    mem_write(56, inst("0000 0000 1111 00000 000 01111 0010011"), 4);
    mem_write(60, inst("0000 0001 0000 00000 000 10000 0010011"), 4);
    mem_write(64, inst("0000 0000 0001 00000 000 00000 1110011"), 4);
}

int load_img() {
    if (img_file == NULL) {
        printf("No image is given. Use the default build-in image.\n");
        return 68;
    }

    FILE *fp = fopen(img_file, "rb");
    assert(fp != NULL);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    printf("The image is %s, size = %ld\n", img_file, size);

    fseek(fp, 0, SEEK_SET);
    int ret = fread(guest_to_host(RESET_VECTOR), size, 1, fp);
    assert(ret == 1);

    fclose(fp);
    return size;
}

void init_monitor(int argc, char *argv[])
{
    contextp = new VerilatedContext;
    IFDEF(CONFIG_WAVE, tfp = new VerilatedVcdC);
    top = new Vtop{contextp};
    contextp->commandArgs(argc, argv);

    contextp->traceEverOn(true);
    IFDEF(CONFIG_WAVE, top->trace(tfp, 0));
    IFDEF(CONFIG_WAVE, tfp->open("./sim/wave.vcd"));

    reset(10);
    isa_reg_read();

    init_mem();

    parse_args(argc, argv);
    long img_size = load_img();

    IFDEF(CONFIG_DEVICE, init_device());

    sdb_init();

    IFDEF(DIFF_TEST, init_difftest(diff_so_file, img_size, difftest_port));

    IFDEF(ITRACE, init_disasm("riscv32"));
}

void release_monitor()
{
    sdb_release();
    IFDEF(CONFIG_WAVE, tfp->close());
    delete top;
    IFDEF(CONFIG_WAVE, delete tfp);
    delete contextp;
}