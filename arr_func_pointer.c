#include <stdio.h>

typedef void fv(int), (*pfv)();

static unsigned int x = 0;

pfv signal(int a, pfv b) {
    b();
    printf("inside signal: %d\n", a);
    return b;
}

void test() { x++; }

// Declare an array of three pointers to functions and invoke the appropriate
// function based on an index value passed in as an argument

typedef int (*settler)();

int f1() { return 1; }

int f2() { return 2; }

int f3() { return 3; }

int main(void) {
    int x = 1;
    int y = 18899999;
    int z = 3;

    int *a[] = {&x, &y, &z};

    float d = 3.1;
    float *pd = &d;

    pd = (double *)&d; // tried to cast to int (int *)d;
    printf("casting from int to double: %f\n", *pd);

    int (*func_ptr[])() = {f1, f2, f3};

    int len = sizeof(func_ptr) / sizeof(func_ptr[0]);
    for (int i = 0; i < len; i++) {
        if (i == 2) {
            goto clean_up;
        }
        printf("function ptr: %d\n", func_ptr[i]());
    }

    printf("arr[2]: %d\n", func_ptr[2]()); // 3
    return 0;

clean_up:
    printf("this is goto function\n");
    return 0;
}
