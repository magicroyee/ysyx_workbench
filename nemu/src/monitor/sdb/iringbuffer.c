#include <sdb/iringbuffer.h>
#include <cpu/decode.h>

int irb_init(IRingBuffer *irb, uint32_t size) {
    irb->size = size+1;
    irb->start = 0;
    irb->end = 0;
    irb->buf = malloc(sizeof(char *) * irb->size);
    Assert(irb->buf, "malloc failed");
    for (int i = 0; i < irb->size; i++) {
        irb->buf[i] = malloc(sizeof(char) * LOGBUF_LEN);
        Assert(irb->buf[i], "malloc failed");
    }

    return 0;
}

int irb_free(IRingBuffer *irb) {
    for (int i = 0; i < irb->size; i++) {
        if (irb->buf[i]) {
            free(irb->buf[i]);
        }
    }
    if (irb->buf) {
        free(irb->buf);
    }
    return 0;
}

bool irb_isempty(IRingBuffer *irb) {
    return irb->start == irb->end;
}

bool irb_isfull(IRingBuffer *irb) {
    return (irb->end + 1) % irb->size == irb->start;
}

int irb_push(IRingBuffer *irb, char *str) {
    if (irb_isfull(irb)) {
        return -1;
    }
    if (irb_isempty(irb)) {
        irb->start = irb->end = 0;
    }
    strcpy(irb->buf[irb->end], str);
    RingBuffer_commit_write(irb, 1);
    return 0;
}

int irb_pop(IRingBuffer *irb) {
    if (irb_isempty(irb)) {
        return -1;
    }
    RingBuffer_commit_read(irb, 1);
    return 0;
}

int irb_log(IRingBuffer *irb, char *str) {
    if (!irb_isfull(irb)) {
        irb_push(irb, str);
    } else {
        irb_pop(irb);
        irb_push(irb, str);
    }
    return 0;
}

void irb_print(IRingBuffer *irb) {
    int i = irb->start;
    while (i != irb->end) {
        printf("%s\n", irb->buf[i]);
        i = (i + 1) % irb->size;
    }
}
