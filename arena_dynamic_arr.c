#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define ARENA_SIZE 4096 // 4KB memory

typedef uint64_t U64;

typedef struct {
    size_t offset;
    U64 memory[ARENA_SIZE];
} Arena;


// create or destroy a 'stack' - an "arena"
Arena *ArenaAlloc(void);
void ArenaRelease(Arena *arena);

// push some bytes onto the 'stack' - the way to allocate
void *ArenaPush(Arena *arena, U64 size);
void *ArenaPushZero(Arena *arena, U64 size);

// some macro helpers that I've found nice:
#define PushArray(arena, type, count)                                          \
    (type *)ArenaPush((arena), sizeof(type) * (count))
#define PushArrayZero(arena, type, count)                                      \
    (type *)ArenaPushZero((arena), sizeof(type) * (count))
#define PushStruct(arena, type) PushArray((arena), (type), 1)
#define PushStructZero(arena, type) PushArrayZero((arena), (type), 1)

// pop some bytes off the 'stack' - the way to free
void ArenaPop(Arena *arena, U64 size);

// get the # of bytes currently allocated.
U64 arena_get_pos(Arena *arena) {
    return arena->offset;
}

// also some useful popping helpers:
void ArenaSetPosBack(Arena *arena, U64 pos);
void ArenaClear(Arena *arena);

void arena_init(Arena *arena) { arena->offset = 0; }

void arena_pop(Arena *arena, U64 size) {
    for (int i = size; i >= 0; i--) {
        printf("reset addr: %p, val: %llu\n", &arena->memory[i], arena->memory[i]);
        arena->memory[i] = 0;
    }
    arena->offset -= size;
}

U64 *arena_alloc(Arena *arena, U64 size) {
    if (arena->offset + size > ARENA_SIZE) {
        printf("Arena out of memory\n");
        return NULL;
    }
    U64 *ptr = &arena->memory[arena->offset];
    arena->offset += size;
    return ptr;
}

// example use of the arena to allocate a dynamic array
int main(void) {
    Arena arena;
    arena_init(&arena);
    printf("allocated: %llu\n", arena_get_pos(&arena));

    // allocate an array of 10 unsigned int64 from arena
    int U64_len = 10;
    U64 *array = (U64 *)arena_alloc(&arena, U64_len * sizeof(U64));
    if (!array) {
        return 1;
    }

    // Fill the array with values
    for (int i = 0; i < U64_len; ++i) {
        array[i] = (i + 1) * 99999;
    }

    printf("arena start at: %p -> end at: %p\n", &arena.memory[0],
           &arena.memory[ARENA_SIZE - 1]);
    printf("arena offset at: %lu, size of uint64_t: %lu, max: %llu\n",
           arena.offset, sizeof(uint64_t), UINT64_MAX);

    // Print some values from the array
    for (int i = 0; i < U64_len; ++i) {
        printf("addr: %p, array[%d] = %llu\n", &array[i], i, array[i]);
    }

    printf("allocated: %llu\n", arena_get_pos(&arena));
    // Reset the arena to free the memory
    arena_pop(&arena, U64_len * sizeof(U64));

    printf("after free allocated: %llu\n", arena_get_pos(&arena));

    for (int i = 0; i < U64_len + 1; i++) {
        printf("arena address: %p, value: %llu\n", &arena.memory[i],
               arena.memory[i]);
    }

    // The following example dynamic memory allocation using malloc
    // int *b_array = NULL;
    // b_array = malloc(sizeof(int)*512);
    // if (!b_array) {
    //     return 1;
    // }
    //
    // for (int i = 0; i < 512; i++) {
    //     b_array[i] = 10+i;
    // }

    // No need to free the memory manually since the arena manages it all
    return 0;
}
