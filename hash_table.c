// TODO: Replace all malloc and free using arena allocator
// https://www.gingerbill.org/article/2019/02/16/memory-allocation-strategies-004
#ifndef _HT_C_
#define _HT_C_

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

typedef struct ht ht;

#define INITIAL_CAPACITY 16
#define ARENA_SIZE 4096
#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

// Hash table entry
typedef struct {
    const char *key;
    void *value;
} htc_entry;

struct ht {
    htc_entry *entries; // hash slots
    size_t capacity;    // size of _entries
    size_t length;      // number of items in has table
};

// Hash table iterator
typedef struct {
    const char *key;
    void *value;

    // internal use
    ht *_table;
    size_t _index;
} hti;

ht *htc_create(void);

void htc_destroy(ht *table);

void *htc_get(ht *table, const char *key);

void htc_set(ht *table, const char *key, void *value);

static uint64_t hash_key(const char *key);

size_t htc_length(ht *table);

static const char *htc_set_entry(htc_entry *entries, size_t capacity,
                                 const char *key, void *value, size_t *plength);

hti htc_iterator(ht *table);

bool htc_next(hti *it);

#endif _HT_C_

// STB style header
#ifndef _HTC_IMPLEMENTATION
#define _HTC_IMPLEMENTATION

ht *htc_create(void) {
    ht *table = malloc(sizeof(ht));
    if (table == NULL) {
        return NULL;
    }
    table->length = 0;
    table->capacity = INITIAL_CAPACITY;

    // allocate (zero'd) space for entry buckets.
    table->entries = calloc(table->capacity, sizeof(htc_entry));
    if (table->entries == NULL) {
        free(table);
        return NULL;
    }
    return table;
}

void ht_destroy(ht *table) {
    for (size_t i = 0; i < table->capacity; i++) {
        free((void *)table->entries[i].key);
    }

    free(table->entries);
    free(table);
}

static uint64_t hash_key(const char *key) {
    uint64_t hash = FNV_OFFSET;
    for (const char *p = key; *p; p++) {
        hash ^= (uint64_t)(unsigned char)(*p);
        hash *= FNV_PRIME;
    }
    return hash;
}

void *htc_get(ht *table, const char *key) {
    // AND hash with capacity-1 to ensure it's within entries array.
    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(table->capacity - 1));

    // loop till we find and empty entry.
    while (table->entries[index].key != NULL) {
        if (strcmp(key, table->entries[index].key) == 0) {
            return table->entries[index].value;
        }
        // Key wasnot in this slot, move to the next (linear probing).
        index++;
        if (index >= table->capacity) {
            index = 0;
        }
    }

    return NULL;
}

// Internal function to set an entry (without expanding table)
static const char *htc_set_entry(htc_entry *entries, size_t capacity,
                                 const char *key, void *value,
                                 size_t *plength) {

    uint64_t hash = hash_key(key);
    size_t index = (size_t)(hash & (uint64_t)(capacity-1));
    // loop until we find an empty entry
    while(entries[index].key != NULL) {
        if (strcmp(key, entries[index].key) == 0) {
            entries[index].value = value;
            return entries[index].key;
        }
        // Key wasnot in this slot, move to the next (linear probing).
        index++;
        if (index >= capacity) {
            index = 0;
        }
    }

    // Didn't find key, allocate+copy if needed, then insert it
    if (plength != NULL) {
        key = strdup(key);
        if (key == NULL) {
            return NULL;
        }

        (*plength)++;
    }
    entries[index].key = (char *)key;
    entries[index].value = value;
    return key;
}

// Expand hash table to twice its current size
static bool ht_expand(ht *table) {
    size_t new_capacity = table->capacity * 2;


    return true;
}

#endif HTC_IMPLEMENTATION
