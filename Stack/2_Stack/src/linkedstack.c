#include "../includes/linkedstack.h"
#include <stdlib.h>
#include <stdio.h>

LinkedStack* createLinkedStack(size_t maxSize) {
    LinkedStack *ret = (LinkedStack *)calloc(sizeof(LinkedStack), 1);
    if (!ret) return NULL;
    ret->maxElementCount = maxSize;
    return ret;
}

StackNode* createLinkedStackNode(char data) {
    StackNode *pNewNode;

    pNewNode = (StackNode *)calloc(sizeof(StackNode), 1);
    if (!pNewNode) return NULL;
    pNewNode->data = data;
    return pNewNode;
}

int pushLS(LinkedStack* pStack, StackNode element) {
    if (isLinkedStackFull(pStack) == TRUE) {
        printf("pushLS : the Stack is fulled.\n");
        return FALSE;
    }
    StackNode *pNewNode = createLinkedStackNode(element.data);
    if (isLinkedStackEmpty(pStack) == TRUE) {
        pStack->pTopElement = pNewNode;
        pStack->currentElementCount++;
    } else {
        pNewNode->pLink = pStack->pTopElement;
        pStack->pTopElement = pNewNode;
        pStack->currentElementCount++;
    }
    return TRUE;
}

StackNode* popLS(LinkedStack* pStack) { 
    StackNode *ret = pStack->pTopElement;
    if (isLinkedStackEmpty(pStack) == TRUE) return NULL;
    pStack->pTopElement = ret->pLink;
    pStack->currentElementCount--;
    ret->pLink = NULL;
    return ret;
}

StackNode* peekLS(LinkedStack* pStack) {
    return pStack->pTopElement;
}

void deleteLinkedStack(LinkedStack* pStack) {
    size_t limit = pStack->currentElementCount;
    for (size_t i = 0; i < limit; i++) {
        StackNode *nptr = popLS(pStack);
        free(nptr);
    }
    free(pStack);
}

int isLinkedStackFull(LinkedStack* pStack) {
    return pStack->currentElementCount == pStack->maxElementCount ? TRUE : FALSE;
}

int isLinkedStackEmpty(LinkedStack* pStack) {
    return pStack->currentElementCount == 0 ? TRUE : FALSE;
}

void displayLinkedStack(LinkedStack *pStack) {
    if (!pStack) return ;
    printf("==================================\n");
    if (pStack->currentElementCount == 0) {
        printf("Stack_Top_Value : None\nStack_Current_Size : %zu\nStack_Max_Size : %zu\n",
            pStack->currentElementCount,
            pStack->maxElementCount);
    } else {
        printf("Stack_Top_Value : %c\nStack_Current_Size : %zu\nStack_Max_Size : %zu\n",
            peekLS(pStack)->data,
            pStack->currentElementCount,
            pStack->maxElementCount);
    }
}
