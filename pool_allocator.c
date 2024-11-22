#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

bool is_power_two(uintptr_t x) { return (x & (x - 1)) == 0; }

uintptr_t align_forward_uintptr(uintptr_t ptr, uintptr_t align) {
    uintptr_t a, p, modulo;

    assert(is_power_two(align));

    a = align;
    p = ptr;

    modulo = p & (a - 1);
    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

size_t align_forward_size(size_t ptr, size_t align) {
    size_t a, p, modulo;

    assert(is_power_two((uintptr_t)align));

    a = align;
    p = ptr;

    modulo = p & (a - 1);
    printf("modulo: %lu\n", modulo);
    printf("size_t: %lu\n", p);
    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT 8
#endif

typedef struct Pool_Free_Node Pool_Free_Node;
struct Pool_Free_Node {
    Pool_Free_Node *next;
};

typedef struct Pool Pool;
struct Pool {
    unsigned char *buf;
    size_t buf_len;
    size_t chunk_size;

    Pool_Free_Node *head;
};

void pool_free_all(Pool *p);

void pool_init(Pool *p, void *backing_buffer, size_t backing_buffer_length,
               size_t chunk_size, size_t chunk_alignment) {
    // Align backing buffer to the specified chunk alignment
    uintptr_t initial_start = (uintptr_t)backing_buffer;
    uintptr_t start =
        align_forward_uintptr(initial_start, (uintptr_t)chunk_alignment);
    backing_buffer_length -= (size_t)(start - initial_start);

    // Align chunk size up to the required chunk_alignment
    chunk_size = align_forward_size(chunk_size, chunk_alignment);

    assert(chunk_size >= sizeof(Pool_Free_Node) && "Chunk size is too small");
    assert(backing_buffer_length >= chunk_size &&
           "Backing buffer length is smaller than the chunk size");

    p->buf = (unsigned char *)backing_buffer;
    p->buf_len = backing_buffer_length;
    p->chunk_size = chunk_size;
    p->head = NULL; // Free List Head

    // Set up the free list for free chunks
    pool_free_all(p);
}

void *pool_alloc(Pool *p) {
    Pool_Free_Node *node = p->head;

    if (node == NULL) {
        assert(0 && "Pool allocator has no free memory");
        return NULL;
    }

    // Pop free node
    p->head = p->head->next;

    // make sure memory zeroed
    return memset(node, 0, p->chunk_size);
}

void pool_free(Pool *p, void *ptr) {
    Pool_Free_Node *node;

    void *start = p->buf;
    void *end = &p->buf[p->buf_len];

    if (ptr == NULL) {
        // Ignore NULL pointers
        return;
    }

    if (!(start <= ptr && ptr < end)) {
        assert(0 && "Memory is out of bound of the buffer in this pool");
        return;
    }

    // Push free node
    node = (Pool_Free_Node *)ptr;
    node->next = p->head;
    p->head = node;
}

void pool_free_all(Pool *p) {
    size_t chunk_count = p->buf_len / p->chunk_size;
    size_t i;

    for (i = 0; i < chunk_count; i++) {
        void *ptr = &p->buf[i * p->chunk_size];
        Pool_Free_Node *node = (Pool_Free_Node *)ptr;

        // Push free node onto the free list
        node->next = p->head;
        p->head = node;
    }
}

int main(int argc, char **argv) {

    // printf("3 is power two: %d\n", is_power_two(3));
    // printf("256 is power two: %d\n", is_power_two(256));

    // size_t ptr = 15;
    // size_t align = 8;
    // printf("align_forward size: %lu\n", align_forward_size(ptr, align));
    // printf("align_forward uintptr: %lu\n", align_forward_uintptr(29, 32));
    // printf("1 & (1-1) = %d\n", (1 & (1 - 1)));
    // printf("2 & (2-1) = %d\n", (2 & (2 - 1)));
    // printf("3 & (3-1) = %d\n", (3 & (3 - 1)));
    // printf("8 & (8-1) = %d\n", (8 & (8 - 1)));

    unsigned char backing_buffer[1024];
    Pool p;
    void *a, *b, *c, *d, *e, *f;
    pool_init(&p, backing_buffer, 1024, 64, DEFAULT_ALIGNMENT);

	a = pool_alloc(&p);
	b = pool_alloc(&p);
	c = pool_alloc(&p);
	d = pool_alloc(&p);
	e = pool_alloc(&p);
	f = pool_alloc(&p);

	pool_free(&p, f);
	pool_free(&p, c);
	pool_free(&p, b);
	pool_free(&p, d);

	d = pool_alloc(&p);

	pool_free(&p, a);

	a = pool_alloc(&p);

	pool_free(&p, e);
	pool_free(&p, a);
	pool_free(&p, d);
    return 0;
}
