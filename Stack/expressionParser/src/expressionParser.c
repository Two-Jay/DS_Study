#include "../includes/expressionParser.h"

char *convertInfixToPostFix(const char *expr, size_t expr_len) {
    char *ret = (char *)calloc(sizeof(char), expr_len + 1);
    if (!ret) return NULL; else ret[expr_len] = '\0';
    FixedArrayStack *pStack = createFixedArrayStack(expr_len);
    if (!ret || isClosedBlank(expr, expr_len) == false) {
        free(ret);
        free(pStack);
        return NULL;
    }
    for (size_t i = 0; i < expr_len; i++) {
        ret[i] = expr[i];
    }
    return ret;
}