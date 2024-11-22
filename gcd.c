#include <stdio.h>

int gcd(int a, int b) {
    while (b) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}

int main(void) {
    int x = 45, y = 210;
    int res = gcd(x, y);

    printf("result of gcd: %d\n", res);
    return 0;
}
