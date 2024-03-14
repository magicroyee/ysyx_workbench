#include "npc_init.h"
#include "npc_memory.h"
#include <getopt.h>
#include <assert.h>

char *img_file = NULL;
extern char mem[MEMORY_SIZE];

static int parse_args(int argc, char *argv[]) {
    const struct option table[] = {
        // {"batch"    , no_argument      , NULL, 'b'},
        // {"log"      , required_argument, NULL, 'l'},
        // {"diff"     , required_argument, NULL, 'd'},
        // {"port"     , required_argument, NULL, 'p'},
        // {"help"     , no_argument      , NULL, 'h'},
        // {"elf"      , required_argument, NULL, 'e'},
        {0          , 0                , NULL,  0 },
    };
    int o;
    while ( (o = getopt_long(argc, argv, "-bhl:d:p:e:", table, NULL)) != -1) {
        switch (o) {
        // case 'b': sdb_set_batch_mode(); break;
        // case 'p': sscanf(optarg, "%d", &difftest_port); break;
        // case 'l': log_file = optarg; break;
        // case 'd': diff_so_file = optarg; break;
        // case 'e': sdb_set_elfname(optarg); break;
        case 1: img_file = optarg; return 0;
        default:
            printf("Usage: %s [OPTION...] IMAGE [args]\n\n", argv[0]);
            // printf("\t-b,--batch              run with batch mode\n");
            // printf("\t-l,--log=FILE           output log to FILE\n");
            // printf("\t-d,--diff=REF_SO        run DiffTest with reference REF_SO\n");
            // printf("\t-p,--port=PORT          run DiffTest with port PORT\n");
            // printf("\t-e,--elf=FILE           specify the ELF file\n");
            printf("\n");
            exit(0);
        }
    }
    return 0;
}

int load_img() {
    if (img_file == NULL) {
        printf("No image is given. Use the default build-in image.");
        return 16;
    }

    FILE *fp = fopen(img_file, "rb");
    assert(fp != NULL);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);

    printf("The image is %s, size = %ld\n", img_file, size);

    fseek(fp, 0, SEEK_SET);
    int ret = fread(mem, size, 1, fp);
    assert(ret == 1);

    fclose(fp);
    return size;
}