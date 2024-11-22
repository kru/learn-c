#include <stdio.h>

enum Day { Monday = 1, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday };

int main(void) {
    int day = 2;
    switch(day) {
        case Monday:
            printf("Monday\n");
            break;
        case Tuesday:
            printf("Tuesday\n");
            break;
        case Wednesday:
            printf("Wednesday\n");
            break;
        default:
            printf("not a valid day\n");
            break;
    }
    return 0;
}
