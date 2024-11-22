#include <stdio.h>

void swap(int *pa, int *pb);

int main() {
    int a = 10;
    int b = 12;

    printf("init -> value a: %d, value b: %d\n", a, b);
    swap(&a, &b);
    printf("main -> value a: %d, value b: %d\n", a, b);
    return 0;
}

void swap(int *pa, int *pb) {
    int t = *pa;
    *pa = *pb;
    *pb = t;
    printf("swap -> value a: %d, value b: %d\n", *pa, *pb);
}
