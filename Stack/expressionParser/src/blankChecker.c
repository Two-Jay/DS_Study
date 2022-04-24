#include "../includes/expressionParser.h"

static bool isOpenerBlank(const char input) {
    return (input == '(' || input == '{' || input == '[');
}

static bool isCloserBlank(const char input) {
    return (input == ')' || input == '}' || input == ']');
}

static bool isTwinBlank(const char openned, const char closed) {
    if (openned == '(' && closed == ')') return true;
    if (openned == '{' && closed == '}') return true;
    if (openned == '[' && closed == ']') return true;
    return false;
}

bool isClosedBlank(const char *str, size_t len) {
    int ret = true;
    FixedArrayStack *fas = createFixedArrayStack(len);
    if (!fas) return false;
    FASNode *nptr;
    for (size_t i = 0; i < len && ret == true; i++) {
        if (isOpenerBlank(str[i]) == true) {
            nptr = createFASNode(str[i]);
            pushFAS(fas, *nptr);
            free(nptr);
        } else if (isCloserBlank(str[i]) == true) {
            if (fas->currentElementCount == 0) {
                ret = false;
            } else {
                nptr = popFAS(fas);
                if (isTwinBlank(nptr->data, str[i]) == false) ret = false;
                free(nptr);
            }
        }
    }
    if (isFixedArrayStackEmpty(fas) == false) ret = false;
    deleteFixedArrayStack(fas);
    return ret;
};