#include <sdb/dtrace.h>
#include <stdio.h>

void dtrace(uint32_t offset, uint32_t len, DTraceType type, const char *name)
{
    printf("DTrace: %s %s offset = %d, len = %d, \n", type == DTRACE_READ ? "DTRACE_READ" : "DTRACE_WRITE", name, offset, len);
}
