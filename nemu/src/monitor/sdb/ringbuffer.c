#include <sdb/ringbuffer.h>
#include <cpu/decode.h>

int rb_init(RingBuffer *rb, uint32_t size) {
    rb->size = size+1;
    rb->start = 0;
    rb->end = 0;
    rb->buf = malloc(sizeof(char *) * rb->size);
    Assert(rb->buf, "malloc failed");
    for (int i = 0; i < rb->size; i++) {
        rb->buf[i] = malloc(sizeof(char) * LOGBUF_LEN);
        Assert(rb->buf[i], "malloc failed");
    }

    return 0;
}

int rb_free(RingBuffer *rb) {
    for (int i = 0; i < rb->size; i++) {
        if (rb->buf[i]) {
            free(rb->buf[i]);
        }
    }
    if (rb->buf) {
        free(rb->buf);
    }
    return 0;
}

bool rb_isempty(RingBuffer *rb) {
    return rb->start == rb->end;
}

bool rb_isfull(RingBuffer *rb) {
    return (rb->end + 1) % rb->size == rb->start;
}

int rb_push(RingBuffer *rb, char *str) {
    if (rb_isfull(rb)) {
        return -1;
    }
    if (rb_isempty(rb)) {
        rb->start = rb->end = 0;
    }
    strcpy(rb->buf[rb->end], str);
    RingBuffer_commit_write(rb, 1);
    return 0;
}

int rb_pop(RingBuffer *rb) {
    if (rb_isempty(rb)) {
        return -1;
    }
    RingBuffer_commit_read(rb, 1);
    return 0;
}

int rb_log(RingBuffer *rb, char *str) {
    if (!rb_isfull(rb)) {
        rb_push(rb, str);
    } else {
        rb_pop(rb);
        rb_push(rb, str);
    }
    return 0;
}

void rb_print(RingBuffer *rb) {
    int i = rb->start;
    while (i != rb->end) {
        printf("%s\n", rb->buf[i]);
        i = (i + 1) % rb->size;
    }
}
