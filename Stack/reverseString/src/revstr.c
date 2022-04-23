#include "../includes/revstr.h"

char *strrev(const char *str, size_t len) {
    if (len <= 0 || !str) return NULL;
    char *ret = (char *)calloc(sizeof(char), len + 1);
    if (!ret) return NULL;
    ret[len] = '\0';

    FixedArrayStack *pStack = createFixedArrayStack(len);
    if (!pStack) {
        free(ret);
        return NULL;
    }

    for (size_t i = 0; i<len; i++) {
        FASNode *tmp = createFASNode(str[i]);
        pushFAS(pStack, *tmp);
        free(tmp);
    }
    for (size_t i = 0; i<len; i++) {
        FASNode *tmp = popFAS(pStack);
        ret[i] = tmp->data;
        free(tmp);
    }
    deleteFixedArrayStack(pStack);
    return ret;
}