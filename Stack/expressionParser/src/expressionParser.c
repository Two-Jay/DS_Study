#include "../includes/expressionParser.h"
#include <stdio.h>
#include <ctype.h>

bool isOperator(const char a) {
    return (a == '+' || a == '-' || a == '*' || a == '/');
}

static bool isOpenerBlank(const char input) {
    return (input == '(');
};
static bool isCloserBlank(const char input) {
    return (input == ')');
};

bool isSuperbOperator(const char cur, const char top) {
    return ((cur == '*' || cur == '/') && (top == '+' || top == '-'));
}

char *convertInfixToPostFix(const char *expr, size_t expr_len) {
    if (isClosedBlank(expr, expr_len) == false) return NULL;    // 괄호 짝 확인
    char *ret = (char *)calloc(sizeof(char), expr_len + 1);     // return buf 
    if (!ret) return NULL;
    FixedArrayStack *pStack = createFixedArrayStack(expr_len); //stack 
    if (!pStack) {
        free(ret);
        return NULL;
    }
    size_t i = 0;
    FASNode *nptr;
    for (size_t j = 0; j < expr_len; j++) {
        // 숫자, 알파벳일 경우
        if (isalnum(expr[j])){
            ret[i++] = expr[j];
        } else { // 괄호랑 연산자 확인 -> push, pop
            // 연산자일 경우
            if (isOperator(expr[j])) {
                // 우선순위 비교
                // pop : 우선순위 비교해서 expr[j] > pStack[top] push, else push after pop
                if (isFixedArrayStackEmpty(pStack)
                    || isSuperbOperator(expr[j], peekFAS(pStack)->data)
                    || peekFAS(pStack)->data == '(') {
                    nptr = createFASNode(expr[j]);
                    pushFAS(pStack, *nptr);
                    free(nptr);
                } else {
                    nptr = popFAS(pStack);
                    ret[i++] = nptr->data;
                    free(nptr);
                    nptr = createFASNode(expr[j]);
                    pushFAS(pStack, *nptr);
                    free(nptr);
                }
            } else if (isOpenerBlank(expr[j])) {    // 여는 괄호
                nptr = createFASNode(expr[j]);
                pushFAS(pStack, *nptr);
                free(nptr);
            } else if (isCloserBlank(expr[j])) {      // 닫는 괄호
                while (peekFAS(pStack)->data != '(') {
                    nptr = popFAS(pStack);
                    ret[i++] = nptr->data;
                    free(nptr);
                }
                nptr = popFAS(pStack);
                free(nptr);
            }            
        }
    }
    while (peekFAS(pStack)){
        nptr = popFAS(pStack);
        ret[i++] = nptr->data;
        free(nptr);
    }
    ret[i] = '\0';
    return (ret);
}