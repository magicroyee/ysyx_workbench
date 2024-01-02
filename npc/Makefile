CFLAGS=--cc --exe --build --j 0 -Wall --trace

CSOURCES=$(wildcard csrc/*.cpp)
VSOURCES=$(wildcard vsrc/*.v)
TARGETS=$(patsubst vsrc/%.v,V%,$(VSOURCES))

$(TARGETS): $(VSOURCES) $(CSOURCES)
	verilator $(CFLAGS) $(VSOURCES) $(CSOURCES)

all:
	@echo "Write this Makefile by your self."

sim: $(TARGETS) 
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	./obj_dir/$(TARGETS)

include ../Makefile
