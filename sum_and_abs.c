#include <stdio.h>

void update(int *a, int *b) {
    int c = *a;
    *a  = ((*a) + (*b));
    *b  = (c > (*b) ? (c-(*b)) : ((*b)-c));
}

int main() {
    int a, b;
    int *pa = &a, *pb = &b;
    
    scanf("%d %d", &a, &b);
    update(pa, pb);
    printf("%d\n%d\n", a, b);

    return 0;
}
