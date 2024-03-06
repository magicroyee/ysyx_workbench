#ifndef __CPU_IRINGBUFFER_H__
#define __CPU_IRINGBUFFER_H__

#include <common.h>

typedef struct {
    uint32_t start;
    uint32_t end;
    uint32_t size;
    char **buf;
} IRingBuffer;


#define RingBuffer_commit_read(B, A) ((B)->start = ((B)->start + (A)) % (B)->size)
#define RingBuffer_commit_write(B, A) ((B)->end = ((B)->end + (A)) % (B)->size)

int irb_init(IRingBuffer *irb, uint32_t size);
int irb_free(IRingBuffer *irb);
bool irb_isempty(IRingBuffer *irb);
bool irb_isfull(IRingBuffer *irb);
int irb_push(IRingBuffer *irb, char *str);
int irb_pop(IRingBuffer *irb);
int irb_log(IRingBuffer *irb, char *str);
void irb_print(IRingBuffer *irb);

#endif