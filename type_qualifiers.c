#include <stdio.h>

void f(unsigned int n, int *restrict p, int *restrict q) {
    while (n-- > 0) {
        printf("before %d\n", *p);
        *p++ = *q++;
        printf("after %d\n", *p);
    }
}

int main(void) {

    const int i = 1;
    // i = 2; -> throw error
    int *ip = (int *)&i;
    *ip = 20;
    printf("const type qualifier i: %d\n", *ip);

    int p = 3;
    int q = 11;
    f(2, &p, &q);
    printf("p: %d, q: %d\n", p, q);
    return 0;
}
