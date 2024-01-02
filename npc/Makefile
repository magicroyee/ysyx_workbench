CFLAGS=--cc --exe --build --j 0 -Wall --trace

CSOURCES=$(wildcard csrc/*.c)
VSOURCES=$(wildcard vsrc/*.v)

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	@echo "Write this Makefile by your self."
	verilator $(CFLAGS) $(VSOURCES) $(CSOURCES)

include ../Makefile
