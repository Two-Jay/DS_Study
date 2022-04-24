#include "./includes/tester.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 2) return 0;
    printf("inserted input : [%s] :)\n", argv[1]);
    testfield(argv[1], strlen(argv[1]));
    return 0;
}