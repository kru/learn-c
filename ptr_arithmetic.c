#include <stdint.h>
#include <stdio.h>

#define array_length(arr) (sizeof(arr) == 0 ? 0 : sizeof(arr) / sizeof(arr[0]));

int main(void) {

    int arr[] = {0, 2, 4, 16};

    int *pa = arr;
    int len = array_length(arr);
    printf("array len: %d\n", len);
    printf("addres arr: %p\n", &arr[0]);
    printf("address pa: 0x%02x\n", pa[3] ^ 1);
    printf("size of int: %lu\n", sizeof(signed int));

    for (int i = 0; i < len; i++) {
        printf("top: %d\n", pa[i]);
        // NOTE: this will change value pa point to which is arr
        pa[i] = pa[i] + 1;
    }

    for (int i = 0; i < len; i++) {
        printf("bot: %d\n", pa[i]);
    }
    return 0;
}
