#include <stdio.h>
#include <string.h>

struct inner {
    int val;
    int type;
} in;

// declare an object identified by sigline that
// has type is struct sigrecord and
// a pointer to sigline object identified by sigline_p
struct sigrecord {
    int signum;
    char signame[20];
    char sigdesc[100];
    struct inner in;
} sigline, *sigline_p;

int main(void) {
    // . access struct
    // -> access pointer of struct
    // struct sigrecord *sigline_p = &(struct sigrecord){10,"",""};
    sigline.signum = 2;
    // NOTE: line below will throw segfault, pointer need to check NULL pointer
    // sigline_p->signum = 3;
    printf("before check num: %d, name: %s\n", sigline.signum, sigline.signame);
    if (sigline_p == NULL) {
        sigline_p = &sigline;
        // alternatively: 
        // sigline_p = &(struct sigrecord){0, "", ""};
        printf("inside check num: %d, name: %s\n", sigline_p->signum, sigline_p->signame);
        sigline_p->signum = 10;
        sigline.signum = 11;
        // sigline_p->signame = "kr_pamungkas";
        char name[] = "kr_pamungkas";
        // int name_len = sizeof(name) / sizeof(name[0]);
        for (int i = 0; i < strlen(name); i++) {
            sigline_p->signame[i] = name[i];
            sigline.signame[i] = name[i] + 2;
        }

        sigline_p->in.val = 30;
    }

    printf("sigline object -> num: %d, name: %s\n", sigline.signum, sigline.signame);
    printf("sigline_p pointer num: %d, name: %s\n", sigline_p->signum, sigline_p->signame);
    printf("sigline_p pointer inside in: %d\n", sigline_p->in.val);
    return 0;
}
