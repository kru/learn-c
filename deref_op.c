#include <stdio.h>
#include <stdbool.h>

int main(void) {
    int i = 17;
    int *ip = &i;

    printf("1. %p\n", ip);

    ip = &*ip;
    printf("2. %p\n", ip);
    printf("value: %d\n", *ip);


    int j = 18;
    int *iq = &j;

    // C89 backward
    // int z = *iq + 31;
    // iq = &z;

    // C99 onward A.K.A compound literal
    // iq = &(int){*iq + 31};

    printf("address before change: %d\n", *iq);
    iq = (&*iq + 31); // pointer arithmetic
    printf("pointer change value: %d\n", *iq);
    return 0;
}
