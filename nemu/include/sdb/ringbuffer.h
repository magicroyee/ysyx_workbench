#ifndef __CPU_RingBuffer_H__
#define __CPU_RingBuffer_H__

#include <common.h>

typedef struct {
    uint32_t start;
    uint32_t end;
    uint32_t size;
    char **buf;
} RingBuffer;


#define RingBuffer_commit_read(B, A) ((B)->start = ((B)->start + (A)) % (B)->size)
#define RingBuffer_commit_write(B, A) ((B)->end = ((B)->end + (A)) % (B)->size)

int rb_init(RingBuffer *rb, uint32_t size);
int rb_free(RingBuffer *rb);
bool rb_isempty(RingBuffer *rb);
bool rb_isfull(RingBuffer *rb);
int rb_push(RingBuffer *rb, char *str);
int rb_pop(RingBuffer *rb);
int rb_log(RingBuffer *rb, char *str);
void rb_print(RingBuffer *rb);

#endif