#include <stdio.h>

int main(void) {
    // int a = 0;
    // for (int i = 0; i < 10; i++) {
    //     printf("hollaA\n");
    // }

    char *str = "Hello";
    printf("%c\n", *str);
    printf("%p\n", str);
    printf("%c\n", *str+1);
    return 0;
}
