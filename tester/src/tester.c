#include "../includes/tester.h"
#include <stdbool.h>
#include <string.h>

bool testfield(const char *input, const bool expected) {
    char *buf;
    buf = convertInfixToPostFix(input, strlen(input));
    printf("converted input : [%s]\n", buf);
    free(buf);
    if (expected == true) return true;
    return false;
};