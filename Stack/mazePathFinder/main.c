#include "./includes/linkedstack.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    Data *data;

    if (argc != 2) return 0;
    printf("inserted path : [%s] :)\n", argv[1]);
    parseMapFile(data, argv[1]);
    findPath(Data);
    return 0;
}