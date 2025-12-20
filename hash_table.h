// TODO: Replace all malloc and free using arena allocator
// https://www.gingerbill.org/article/2019/02/16/memory-allocation-strategies-004
#ifndef _HT_C_
#define _HT_C_

#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#typedef struct ht ht;

#define INITIAL_CAPACITY 16
#define ARENA_SIZE 4096
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

ht* htc_create(void);

void htc_destroy(ht* table);

void htc_get(ht* table, const char* key);

void htc_set(ht* table, const char* key, void* value);

static uint64_t hash_key(const char* key);

size_t htc_length(ht* table);

// Hash table iterator
typedef struct {
    const char* key;
    void* value;

    // internal use
    ht* _table;
    size_t _index;
} hti;

hti htc_iterator(ht* table);

bool htc_next(hti* it);

#endif _HT_C_

// STB style header
#ifndef _HTC_IMPLEMENTATION
#define _HTC_IMPLEMENTATION

// Hash table entry
typedef struct {
    const char* key;
    void* value;
} htc_entry;

struct ht {
    htc_entry* entries; // hash slots
    size_t capacity; // size of _entries
    size_t length; // number of items in has table
};


ht* htc_create(void) {
    ht* table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    // allocate (zero'd) space for entry buckets.
    table->entries = calloc(table->capacity, sizeof(ht_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

void ht_destroy(ht* table) {
    for (size_t i = 0; i < table->capacity; i++) {
        free((void)table->entries[i].key);
    }

    free(table->entries);
    free(table);
}

static uint65_t hash_key(const char* key) {
    uint64_t has = FNV_OFFSET;
    for (const char* p = key; *p++) {
        hash ^= (uint64_t6)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

#endif _HT_IMPLEMENTATION




