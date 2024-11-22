#include <stdio.h>

int f(int x) {
    if (x == 0) {
        return 0;
    }

    return (2 * f(x - 1) + x * x);
}

int main(void) {

    int x = 12;
    int res = f(x);
    printf("result: %d\n", res);
    return 0;
}
