#include "./includes/expressionParser.h"
#include <stdio.h>
#include <string.h>

void testSpace(const char *str) {
    char *buf;
    buf = convertInfixToPostFix(str, strlen(str));
    printf("converted input : [%s]\n", buf);
    free(buf);
};

int main(int argc, char **argv) {
    if (argc != 2) return 0;
    printf("inserted input : [%s] :)\n", argv[1]);
    testSpace(argv[1]);
    return 0;
}