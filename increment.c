#include <stdio.h>

static unsigned int counter = 0;
void increment(void) {
    // because we use static
    // then, storage duration is static
    // therefore, the counter lifetime available at entire program execution
    // 1,2,3,4,5
    counter++;
    // printf("%d ", counter);
}

int retriever() {
    return counter;
}

int main(void) {
    for (int i = 0; i < 5; i++) {
        increment();
    }

    int cur = retriever();
    printf("counter cur val: %d\n", cur);

    return 0;
}
