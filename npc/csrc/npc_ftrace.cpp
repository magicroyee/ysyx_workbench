#include "npc_ftrace.h"
#include "debug.h"

func_tab ftab;
char *shstrtab;
char *strtab;
char ftrace_buf[LOG_BUF_LEN];
int indent = 0;
bool init_flag = false;

static inline void func_tab_add(Elf32_Sym sym) {
    Assert(ftab.size < FUNC_TAB_SIZE, "function table overflow");
    ftab.tab[ftab.size++] = sym;
}

int npc_ftrace_init(const char *elfname) {
    // printf("npc_ftrace_init\n");
    ftab.size = 0;
    indent = 0;

    FILE *fp;
    Elf32_Ehdr ehdr;
    Elf32_Shdr shdr;
    Elf32_Shdr *symhdr = NULL;
    Elf32_Shdr *strhdr = NULL;
    Elf32_Sym sym;

    fp = fopen(elfname, "rb");
    if (fp == NULL) {
        printf("Error: No such file: %s\n", elfname);
        return -1;
    }

    Assert(fread(&ehdr, 1, sizeof(ehdr), fp) == sizeof(ehdr), "fread failed");

    if(memcmp(ehdr.e_ident, ELFMAG, SELFMAG) != 0) {
        printf("Error: ELF magic number error\n");
        return -1;
    }

    fseek(fp, ehdr.e_shoff + ehdr.e_shstrndx * sizeof(shdr), SEEK_SET);
    Assert(fread(&shdr, 1, sizeof(shdr), fp) == sizeof(shdr), "fread failed");

    shstrtab = (char*)malloc(shdr.sh_size);
    Assert(shstrtab, "malloc failed");
    fseek(fp, shdr.sh_offset, SEEK_SET);
    Assert(fread(shstrtab, 1, shdr.sh_size, fp) == shdr.sh_size, "fread failed");

    for (int i = 0; i < ehdr.e_shnum; i++) {
        fseek(fp, ehdr.e_shoff + i * sizeof(shdr), SEEK_SET);
        Assert(fread(&shdr, 1, sizeof(shdr), fp) == sizeof(shdr), "fread failed");

        if (strcmp(&shstrtab[shdr.sh_name], ".symtab") == 0) {
            symhdr = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
            *symhdr = shdr;
        }
        if (strcmp(&shstrtab[shdr.sh_name], ".strtab") == 0) {
            strhdr = (Elf32_Shdr*)malloc(sizeof(Elf32_Shdr));
            *strhdr = shdr;
        }
    }

    Assert(symhdr && strhdr, "no .symtab or .strtab found");

    strtab = (char *)malloc(strhdr->sh_size);
    Assert(strtab, "malloc failed");
    fseek(fp, strhdr->sh_offset, SEEK_SET);
    Assert(fread(strtab, 1, strhdr->sh_size, fp) == strhdr->sh_size, "fread failed");

    fseek(fp, symhdr->sh_offset, SEEK_SET);
    for (int i = 0; i < symhdr->sh_size / sizeof(sym); i++) {
        Assert(fread(&sym, 1, sizeof(sym), fp) == sizeof(sym), "fread failed");
        if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC) {
            ftab.tab[ftab.size++] = sym;
        }
    }

    init_flag = true;

    fclose(fp);
    free(strhdr);
    free(symhdr);

    return 0;
}

void npc_ftrace_release() {
    free(shstrtab);
    free(strtab);
}

const char *npc_ftrace_lookup(uint32_t addr) {
    Assert(strtab, "function table not initialized");
    for (int i = 0; i < ftab.size; i++) {
        if (ftab.tab[i].st_value <= addr && addr < ftab.tab[i].st_value + ftab.tab[i].st_size) {
            return &strtab[ftab.tab[i].st_name];
        }
    }
    return "???";
}

void npc_ftrace(word_t addr, word_t pc, int rd, int rs1) {
    int fcall_flag = 0;
    int fret_flag = 0;

    if (!init_flag) {
        return;
    }

    fcall_flag = (rd == 1);
    fret_flag = (rd == 0) && (rs1 == 1);

    if (fcall_flag) {
        indent++;
        // sprintf(ftrace_buf, "[FTRACE:%08x] %*scall %s", pc, indent, "", npc_ftrace_lookup(addr));
    }
    else if (fret_flag){
        // sprintf(ftrace_buf, "[FTRACE:%08x] %*sret %s", pc, indent, "", npc_ftrace_lookup(pc));
        indent--;
    }

    if (fcall_flag || fret_flag) {
        printf("%s\n", ftrace_buf);
    }
}