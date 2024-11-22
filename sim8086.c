#include <stdio.h>

void print_binary(unsigned int num);
void print_int_array_binary(unsigned char *array, size_t size);

char *OPCODE[] = {
    "100010", // MOV
    "1011"    //
};

// REG
char *REG[8][3] = {
    {"000", "AL", "AX"}, /* testing comment */
    {"001", "CL", "CX"}, {"010", "DL", "DX"}, {"011", "BL", "BX"},
    {"100", "AH", "SP"}, {"101", "CH", "BP"}, {"110", "DH", "SI"},
    {"111", "BH", "DI"},
};

int main(int argc, char **argv) {
    FILE *f = NULL;

    printf("argc: %d\n", argc);
    if (argc < 2) {
        printf("You need to specify the input file!\n");
        fprintf(stderr, "Usage: %s filename", argv[0]);
        return 1;
    }

    printf("argv: %s\n", argv[1]);

    f = fopen(argv[1], "r");
    if (f == NULL) {
        perror("Error opening file...");
        return 1;
    }

    unsigned char buffer[256];
    size_t bytesRead;
    char *bytes = {""};

    bytesRead = fread(buffer, 1, sizeof(buffer), f);
    printf("file len: %zu\n", bytesRead);
    print_int_array_binary(buffer, bytesRead);
    // while (bytesRead > 0) {
    //
    //   for (size_t i = 0; i < bytesRead; i++) {
    //     printf("%02x ", buffer[i]);
    //   }
    //   printf("\n");
    //   bytesRead--;
    // }

    return 0;
}

void print_binary(unsigned int num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

void print_int_array_binary(unsigned char *array, size_t size) {
    printf("Array elements in binary:\n");
    for (size_t i = 0; i < size; i++) {
        printf("%d\n", array[i]);
        printf("casting to bin: %d\n", array[i] & 0);
        print_binary(array[i]);
    }
    printf("\n");
}
