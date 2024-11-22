#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} item;

int cmp(const void* a, const void* b) {
    item* item_a = (item*) a;
    item* item_b = (item*) b;
    // printf("item_a: %s, item_b: %s\n", item_a->key, item_b->key);
    return strcmp(item_a->key, item_b->key);
}

item binary_search(item* items, size_t size, const char* key) {

}

int main(void) {
    item items[] = {
        {"bar", 200}, {"bazz", 110}, {"bob", 11}, {"buzz", 7},{"foo", 10},
        {"jane", 100}, {"x", 200}
    };
    size_t num_items = sizeof(items) / sizeof(item);

    item key = {"bob", 0};
    item* found = bsearch(&key, items, num_items, sizeof(item), cmp); // items must be sorted first

    if (!found) {
        printf("not found\n");
        return 1;
    }

    printf("bsearch from stdlib.h, found: %d\n", found->value);

}
