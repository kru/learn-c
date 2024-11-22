#include <stdio.h>

union tree {
    struct {
        int type;
    } n;
    struct {
        int type;
        int int_node;
    } ni;
    struct {
        int type;
        double double_node;
    } nf;
} u;


void set_values(union tree *tr) {
    if (tr == NULL) {
        tr = &u;
    }

    tr->n.type = 3;
    tr->ni.type = 1;
    tr->ni.int_node = 11;

    tr->nf.type =2;
    tr->nf.double_node = 3.141;
}

int main(void) {
    u.nf.type = 1;
    u.nf.double_node = 3.14;

    printf("u.nf.double_node: %.3f\n", u.nf.double_node);

    union tree *tr = &u;
    set_values(tr);
    printf("u->nf.double_node: %.3f\n", u.nf.double_node);
    return 0;
}
