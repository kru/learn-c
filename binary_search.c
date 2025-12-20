#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} item;

int cmp(const void *a, const void *b) {
    item *item_a = (item *)a;
    item *item_b = (item *)b;
    // printf("item_a: %s, item_b: %s\n", item_a->key, item_b->key);
    return strcmp(item_a->key, item_b->key);
}

// item binary_search(item *items, size_t size, const char *key) {
//     if (items == NULL) {
//         return *items;
//     }
//
//     size_t low = 0;
//     size_t mid = size / 2;
//
//     while (low < size) {
//         if (strcmp(items[low].key, key) == 0) {
//             return items[low];
//         }
//     }
// }

// this is binary search implementation in linux kernel
// its beautiful
typedef int (*cmp_func_t)(const void *a, const void *b);
void *__inline_bsearch(const void *key, const void *base, size_t num,
                      size_t size, cmp_func_t cmp) {
    const char *pivot;
    int result;

    while (num > 0) {
        pivot = base + (num >> 1) * size;
        item *pivot_item = (item *)pivot;

        printf("num :%lu, pivot: {key: %s, value: %d}, result: %d\n", num,
               pivot_item->key, pivot_item->value, result);

        result = cmp(key, pivot);

        if (result == 0)
            return (void *)pivot;

        if (result > 0) {
            base = pivot + size;
            num--;
        }
        num >>= 1;
    }

    return NULL;
}

int main(void) {
    item items[] = {{"bar", 200}, {"bazz", 110}, {"bob", 11}, {"buzz", 7},
                    {"foo", 10},  {"jane", 100}, {"x", 200}};
    size_t num_items = sizeof(items) / sizeof(item);

    item key = {"jane", 0};
    item *found = __inline_bsearch(&key, items, num_items, sizeof(item),
                                  cmp); // items must be sorted first

    if (!found) {
        printf("not found\n");
        return 1;
    }

    printf("bsearch from stdlib.h, found: %d\n", found->value);
}
