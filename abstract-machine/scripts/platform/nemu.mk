AM_SRCS := platform/nemu/trm.c \
           platform/nemu/ioe/ioe.c \
           platform/nemu/ioe/timer.c \
           platform/nemu/ioe/input.c \
           platform/nemu/ioe/gpu.c \
           platform/nemu/ioe/audio.c \
           platform/nemu/ioe/disk.c \
           platform/nemu/mpe.c

CFLAGS    += -fdata-sections -ffunction-sections
LDFLAGS   += -T $(AM_HOME)/scripts/linker.ld \
             --defsym=_pmem_start=0x80000000 --defsym=_entry_offset=0x0
LDFLAGS   += --gc-sections -e _start
NEMUFLAGS += -l $(shell dirname $(IMAGE).elf)/nemu-log.txt
ifeq ($(FTRACE),y)
  NEMUFLAGS += -e $(shell dirname $(IMAGE).elf)/$(NAME)-riscv32-nemu.elf
endif
ifeq ($(BATCH),y)
  NEMUFLAGS += -b
endif

CFLAGS += -DMAINARGS=\"$(mainargs)\"
CFLAGS += -I$(AM_HOME)/am/src/platform/nemu/include
.PHONY: $(AM_HOME)/am/src/platform/nemu/trm.c

PLATFORM_CLEAN = nemu-clean

image: $(IMAGE).elf
	@$(OBJDUMP) -d $(IMAGE).elf > $(IMAGE).txt
	@echo + OBJCOPY "->" $(IMAGE_REL).bin
	@$(OBJCOPY) -S --set-section-flags .bss=alloc,contents -O binary $(IMAGE).elf $(IMAGE).bin

run: image
	$(MAKE) -C $(NEMU_HOME) ISA=$(ISA) run ARGS="$(NEMUFLAGS)" IMG=$(IMAGE).bin
	
# run-batch: NEMUFLAGS += -e /home/zhu/workspace/ysyx-workbench/am-kernels/tests/cpu-tests/build/add-riscv32-nemu.elf
run-batch: image
	$(MAKE) -C $(NEMU_HOME) ISA=$(ISA) run-batch ARGS="$(NEMUFLAGS)" IMG=$(IMAGE).bin

gdb: image
	$(MAKE) -C $(NEMU_HOME) ISA=$(ISA) gdb ARGS="$(NEMUFLAGS)" IMG=$(IMAGE).bin

$(PLATFORM_CLEAN):
	echo \# Cleaning $(NEMU_HOME)
	$(MAKE) -C $(NEMU_HOME) clean
.PHONY: $(PLATFORM_CLEAN)