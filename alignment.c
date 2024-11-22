#include <stdio.h>

struct S {
    int i;
    double d;
    char c;
};

enum day { sun, mon, tue, wed, thu, fri, sat };

int main(void) {
    unsigned char bad_buff[sizeof(struct S)];
    _Alignas(struct S) unsigned char good_buff[sizeof(struct S)];

    struct S *bad_s_ptr = (struct S *)bad_buff;
    struct S *good_s_ptr = (struct S *)good_buff;
    good_s_ptr->c = 'c';

    printf("enum day %d \n", sun);
    printf("enum day %c \n", good_s_ptr->c);
    for (int i = 0; i < 10; i++) {
    }
    printf("\n");
}
