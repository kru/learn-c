#include <stdio.h>

void increment(void) {
    static unsigned int counter = 0;

    counter++;
    printf("counter: %d\n", counter);
}

int main(void) {
    for (int i = 0; i < 10; i++) {
        increment();
    }
    return 0;
}
