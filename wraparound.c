#include <stdio.h>
#include <limits.h>

int main(void) {
    unsigned int ui = UINT_MAX;
    ui++;
    printf("ui = %u\n", ui);
    ui--;
    printf("ui = %u\n", ui);
    return 0;
}
