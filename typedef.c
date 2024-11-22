#include <stdio.h>

typedef struct tnode {
    int count;
    struct tnode *left;
    struct tnode *right;
} tnode;

void count_up(tnode *t) {
    t->count = t->count + 1;
}

int main(void) {
   tnode  *t = &(tnode){.count = 0};

    printf("init tnode count: %d\n", t->count);
    count_up(t);
    printf("after tnode count: %d\n", t->count);
    return 0;
}
