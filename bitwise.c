#include <stdint.h>
#include <stdio.h>

void print_binary(uint64_t n) {
    // Assuming we're working with a 64-bit integer
    for (int i = 63; i >= 0; i--) {
        uint64_t bit = (n >> i) & 1;
        printf("%llu", bit);
        if (i % 8 == 0) printf(" ");
    }
    printf("\n");
}

int main(void) {

    uint64_t p = 10;
    // 10 << 1 = 20: 0000 1100 -> 0001 1000
    // 10 << 2 = 40: 0000 1100 -> 0010 1000
    // 10 << 3 = 80: 0000 1100 -> 0010 1000
    p = (10 << 0); // 20

    printf("p<<0: %llu\n", p << 0);
    print_binary(p << 0);
    printf("p<<1: %llu\n", p << 1);
    print_binary(p << 1);
    printf("p<<2: %llu\n", p << 2);
    print_binary(p << 2);
    printf("p<<3: %llu\n", p << 3);
    print_binary(p << 3);
    printf("9<<1: %llu\n", (uint64_t)9 << 1);
    print_binary(18);
    return 0;
}
