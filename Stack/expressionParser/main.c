#include "./includes/expressionParser.h"
#include <stdio.h>
#include <string.h>

bool testfield(const char *input, const bool expected) {
    char *buf;
    buf = convertInfixToPostFix(input, strlen(input));
    printf("converted input : [%s]\n", buf);
    free(buf);
    if (expected == true) return true;
    return false;
};

int main(int argc, char **argv) {
    if (argc != 2) return 0;
    printf("inserted input : [%s] :)\n", argv[1]);
    testfield(argv[1], true);
    return 0;
}