#ifndef __DTRACE_H__
#define __DTRACE_H__

#include <stdint.h>

typedef enum { DTRACE_READ, DTRACE_WRITE } DTraceType;

void dtrace(uint32_t offset, uint32_t len, DTraceType type, const char *name);

#endif