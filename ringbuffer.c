#include <stdio.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>  // for usleep, optional
#include <time.h>


#define CACHE_LINE		64
#define BUFFER_SLOTS	128		// Power of 2 recommended
#define CHUNK_SIZE		4096	// Typical page-aligned read size

typedef struct {
	size_t len;
	char data[CHUNK_SIZE];
} Slot;

typedef struct {
	_Atomic size_t head __attribute__((aligned(CACHE_LINE)));
    char pad1[CACHE_LINE - sizeof(size_t)];
    _Atomic size_t tail __attribute__((aligned(CACHE_LINE)));
    char pad2[CACHE_LINE - sizeof(size_t)];
    Slot slots[BUFFER_SLOTS];
} SPSCRingBuffer;

void rb_init(SPSCRingBuffer *rb) {
    atomic_store_explicit(&rb->head, 0, memory_order_relaxed);
    atomic_store_explicit(&rb->tail, 0, memory_order_relaxed);
}

// Producer: returns 1 on success, 0 if full
int rb_enqueue(SPSCRingBuffer *rb, const char *data, size_t len) {
	size_t head = atomic_load_explicit(&rb->head, memory_order_relaxed);
    size_t tail = atomic_load_explicit(&rb->tail, memory_order_acquire);
    size_t next_head = (head + 1) & (BUFFER_SLOTS - 1);

	if (next_head == tail) return 0;  // Full

    if (len > CHUNK_SIZE) len = CHUNK_SIZE;  // Truncate if larger
    rb->slots[head].len = len;
    memcpy(rb->slots[head].data, data, len);

    atomic_store_explicit(&rb->head, next_head, memory_order_release);
    return 1;
}

// Consumer: returns length (>0 data, 0 EOF, -1 empty)
ssize_t rb_dequeue(SPSCRingBuffer *rb, char **out_data) {
	size_t head = atomic_load_explicit(&rb->head, memory_order_relaxed);
	size_t tail = atomic_load_explicit(&rb->tail, memory_order_relaxed);

	if (head == tail) return -1; // Empty

	size_t len = rb->slots[tail].len;
	*out_data = rb->slots[tail].data;
	atomic_store_explicit(&rb->tail,
	 	(tail + 1) & (BUFFER_SLOTS - 1), memory_order_release);
	return len; // 0 indicated EOF
}

typedef struct {
	SPSCRingBuffer *rb;
	const char *filename;
} ProducerArgs;

void *producer_thread(void *arg) {
	ProducerArgs *args = arg;
	FILE *fp = fopen(args->filename, "rb");
	if (!fp) {
		perror("fopen");
		return NULL;
	}

	char buffer[CHUNK_SIZE];
	size_t bytes;

	while ((bytes = fread(buffer, 1, CHUNK_SIZE, fp)) > 0) {
		while (!rb_enqueue(args->rb, buffer, bytes)) {
			usleep(1000); // Back-off if buffer full
		}
	}

	// Signal EOF with zero-length slot
	while (!rb_enqueue(args->rb, NULL, 0)) {
		usleep(1000);
	}

	fclose(fp);
	return NULL;
}

void *consumer_thread(void *arg) {
	SPSCRingBuffer *rb = arg;
	char *data;
	ssize_t len;

	while ((len = rb_dequeue(rb, &data)) != 0) {
		if (len > 0) {
			fwrite(data, 1, len, stdout);
		} else if (len == -1) {
			usleep(1000); // Wait if empty
		}
	}

	return NULL;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <text_file>\n", argv[0]);
		return 1;
	}

	clock_t start = clock();
	SPSCRingBuffer rb;
	rb_init(&rb);

	pthread_t prod, cons;
    ProducerArgs pargs = { &rb, argv[1] };

    pthread_create(&prod, NULL, producer_thread, &pargs);
    pthread_create(&cons, NULL, consumer_thread, &rb);

    pthread_join(prod, NULL);
    pthread_join(cons, NULL);

    clock_t end = clock();
    double time_taken = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("time taken: %f\n", time_taken);
    return 0;
}