# CFLAGS=--cc --exe --build --j 0 -Wall --trace

# CSOURCES=$(wildcard csrc/*.cpp)
# VSOURCES=$(wildcard vsrc/*.v)
# TARGETS=$(patsubst vsrc/%.v,V%,$(VSOURCES))

# $(TARGETS): $(VSOURCES) $(CSOURCES)
# 	verilator $(CFLAGS) $(VSOURCES) $(CSOURCES)
TOPNAME ?= top
SIMTOPNAME = tb_$(TOPNAME)
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O3 --x-assign fast --x-initial fast --noassert --trace
SIM_CFLAGS += --cc --exe --build --j 0 \
				-O3 --trace --timing

BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
SIM_DIR = ./sim
SIM_OBJ_DIR = $(SIM_DIR)/obj_dir
SIM_BIN = $(SIM_DIR)/$(SIMTOPNAME)

default: $(BIN) $(SIM_BIN)

$(shell mkdir -p $(BUILD_DIR))

# constraint file
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# project source
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp" ! -name "sim*.cpp")
CSRCS += $(SRC_AUTO_BIND)
SIM_CSRCS = $(shell find $(abspath ./csrc) -name "sim*.cpp")

# rules for NVBoard
include $(NVBOARD_HOME)/scripts/nvboard.mk

# rules for verilator
INCFLAGS = $(addprefix -I, $(INC_PATH))
RUN_FLAGS = $(CXXFLAGS) $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\""
SIM_FLAGS = $(CXXFLAGS) $(INCFLAGS) -DTOP_NAME="\"V$(SIMTOPNAME)\""

$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(RUN_FLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))

$(SIM_BIN): $(VSRCS) $(SIM_CSRCS)
	$(shell mkdir -p $(SIM_DIR))
	@rm -rf $(SIM_OBJ_DIR)
	$(VERILATOR) $(SIM_CFLAGS) \
		--top-module $(SIMTOPNAME) $^ \
		$(addprefix -CFLAGS , $(SIM_FLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(SIM_OBJ_DIR) --exe -o $(abspath $(SIM_BIN))

all: default
	@echo "Write this Makefile by your self."

sim: $(SIM_BIN) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	@$^

run: $(BIN)
	$(call git_commit, "run RTL") # DO NOT REMOVE THIS LINE!!!
	@$^

clean:
	rm -rf $(BUILD_DIR) $(SIM_DIR)

include ../../Makefile

.PHONY: default all sim clean