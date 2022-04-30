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
    if (isClosedBlank(expr, expr_len) == false) return NULL;    // 괄호의 짝 체크, 실패시 예외처리
    char *ret = (char *)calloc(sizeof(char), expr_len + 1);     // 버퍼 선언 및 null-guard
    if (!ret) return NULL;
    FixedArrayStack *pStack = createFixedArrayStack(expr_len); // 스텍 선언 및 null-guard 
    if (!pStack) {
        free(ret); // 버퍼는 선언된 상태이므로 해제 후 리턴
        return NULL;
    }
    size_t i = 0; // 복사해줄 버퍼의 인덱스
    FASNode *nptr; // 반복문 내부에서 pop, push 할 때 쓸 노드의 ptr
    // 입력한 문자열로 된 식 전체 탐색
    for (size_t j = 0; j < expr_len; j++) {
        // 숫자, 알파벳일 경우
        if (isalnum(expr[j])){
            // 그대로 버퍼에 복사
            ret[i++] = expr[j];
        } else { // 괄호랑 연산자 확인 -> push, pop
            // 연산자일 경우
            if (isOperator(expr[j])) {
                // 우선순위 비교
                // pop : 우선순위 비교해서 expr[j] > pStack[top] push, else push after pop
                if (isFixedArrayStackEmpty(pStack)
                    || isSuperbOperator(expr[j], peekFAS(pStack)->data)
                    || peekFAS(pStack)->data == '(') {
                    // 현재 인덱스의 연산자 push
                    nptr = createFASNode(expr[j]);
                    pushFAS(pStack, *nptr);
                    free(nptr);
                } else {
                    // 스텍 탑에 있는 연산자 pop
                    nptr = popFAS(pStack);
                    ret[i++] = nptr->data;
                    free(nptr);
                    // 현재 인덱스의 연산자 push
                    nptr = createFASNode(expr[j]);
                    pushFAS(pStack, *nptr);
                    free(nptr);
                }
            } else if (isOpenerBlank(expr[j])) {    
                // 현재 인덱스의 문자가 여는 괄호라면...현재 인덱스 push
                nptr = createFASNode(expr[j]);
                pushFAS(pStack, *nptr);
                free(nptr);
            } else if (isCloserBlank(expr[j])) {
                // 현재 인덱스의 문자가 닫는 괄호라면...
                // 여는 괄호가 나올 때까지의 모든 스텍 노드를 pop
                while (peekFAS(pStack)->data != '(') {
                    nptr = popFAS(pStack);
                    ret[i++] = nptr->data;
                    free(nptr);
                }
                // 넣었던 여는 괄호 노드를 pop으로 처리
                nptr = popFAS(pStack);
                free(nptr);
            }            
        }
    }
    // 전체 인덱스를 탐색하고 남아있는 연산자를 pop
    while (peekFAS(pStack)){
        nptr = popFAS(pStack);
        ret[i++] = nptr->data;
        free(nptr);
    }
    // 버퍼의 null-terminating 이후 리턴
    ret[i] = '\0';
    return (ret);
}