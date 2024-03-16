NAME = klib
SRCS = $(shell find src/ -name "*.c")
ifeq ($(NUK), y)
	CFLAGS += -D__NATIVE_USE_KLIB__
endif
include $(AM_HOME)/Makefile
