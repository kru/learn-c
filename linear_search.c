#include <stdio.h>
#include <string.h>

typedef struct {
    char *key;
    int value;
} item;

item items[] = {{"foo", 10}, {"bar", 200},  {"bazz", 110}, {"buzz", 7},
                {"bob", 11}, {"jane", 100}, {"x", 200}};

item *linear_search(item *items, size_t size, const char *key) {
    for (int i = 0; i < size; i++) {
        if (strcmp(items[i].key, key) == 0) {
            return &items[i];
        }
    }

    return NULL;
}

int main(void) {
    size_t num_items = sizeof(items) / sizeof(item);

    item *found = linear_search(items, num_items, "x");

    if (!found) {
        return 1;
    }

    printf("linear search: value: %d\n", found->value);
    return 0;
}
