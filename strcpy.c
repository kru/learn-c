#include <stdio.h>

void strcopy(char *dest, char *src) {
    while (*dest++ = *src++);
}

int main(void) {
    char test[] = "hello strcopy in here";
    char res[] = "";

    strcopy(res, test);

    printf("test: %s, res: %s\n", test, res);
    return 0;
}
