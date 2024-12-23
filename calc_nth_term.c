#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Complete the following function.

int recurse(int n, int a, int b, int c) {


    return recurse(n-1, a, b, c);
}

int find_nth_term(int n, int a, int b, int c) {
    if (n <= 0) {
        return 0;
    }
    if (n == 1) {
        return a;
    }
    if (n == 2) {
        return b;
    }
    if (n == 3) {
        return c;
    }

    return find_nth_term(n - 1, a, b, c) + find_nth_term(n - 2, a, b, c) + find_nth_term(n - 3, a, b, c);
}

int main() {
    int n, a, b, c;

    scanf("%d %d %d %d", &n, &a, &b, &c);
    int ans = find_nth_term(n, a, b, c);

    printf("%d", ans);
    return 0;
}
