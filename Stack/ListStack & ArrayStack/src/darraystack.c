#include "../includes/darraystack.h"
#include <stdlib.h>
#include <stdio.h>

DynamicArrayStack* createDynamicArrayStack(size_t init_size) {
    DynamicArrayStack *ret = (DynamicArrayStack *)calloc(sizeof(DynamicArrayStack), 1);
    if (!ret) return NULL;
    ret->maxElementCount = init_size;
    ret->pElements = (DASNode *)calloc(sizeof(DASNode), ret->maxElementCount);
    if (!ret->pElements) {
        free(ret);
        return NULL;
    }
    return ret;
}

DASNode *createDASNode(char input) {
    DASNode *ret = (DASNode *)calloc(sizeof(DASNode), 1);
    if (!ret) return NULL;
    ret->data = input;
    return ret;
}

int pushDAS(DynamicArrayStack* pStack, DASNode element) {
    if (isDynamicArrayStackFull(pStack) == TRUE) {
        if (resizeDynamicArrayStack(pStack, pStack->maxElementCount * 2) == FALSE) return FALSE;
    }
    pStack->pElements[pStack->currentElementCount].data = element.data;
    pStack->currentElementCount++;
    return TRUE;
}

DASNode* popDAS(DynamicArrayStack* pStack) {
    if (isDynamicArrayStackEmpty(pStack) == TRUE) return NULL;
    DASNode *currentTopNode = peekDAS(pStack);
    DASNode *ret = createDASNode(peekDAS(pStack)->data);
    if (!ret) return NULL;
    currentTopNode->data = 0;
    pStack->currentElementCount--;
    return ret;
};

DASNode* peekDAS(DynamicArrayStack* pStack) {
    return pStack->currentElementCount == 0
        ? NULL : &(pStack->pElements[pStack->currentElementCount - 1]);
}

int resizeDynamicArrayStack(DynamicArrayStack* pStack, size_t wanted_size) {
    DASNode *buf = (DASNode *)calloc(sizeof(DASNode), wanted_size);
    if (!buf) return FALSE;
    for (size_t i = 0; i < pStack->currentElementCount; i++) {
        buf[i].data = pStack->pElements[i].data;
    }
    free(pStack->pElements);
    pStack->pElements = buf;
    pStack->maxElementCount = wanted_size;
    return TRUE;
}

void deleteDynamicArrayStack(DynamicArrayStack* pStack) {
    if (isDynamicArrayStackEmpty(pStack) == FALSE) free(pStack->pElements);
    free(pStack);
}


int isDynamicArrayStackFull(DynamicArrayStack* pStack) {
    return pStack->currentElementCount == pStack->maxElementCount ? TRUE : FALSE;
}

int isDynamicArrayStackEmpty(DynamicArrayStack* pStack) {
    return pStack->currentElementCount == 0 ? TRUE : FALSE;
}

void displayDynamicArrayStack(DynamicArrayStack *pStack) {
    if (!pStack) return ;
    printf("==================================\n");
    if (pStack->currentElementCount == 0) {
        printf("Stack_Top_Value : None\nStack_Current_Size : %zu\nStack_Max_Size : %zu\n",
            pStack->currentElementCount,
            pStack->maxElementCount);
    } else {
        printf("Stack_Top_Value : %c\nStack_Current_Size : %zu\nStack_Max_Size : %zu\n",
            peekDAS(pStack)->data,
            pStack->currentElementCount,
            pStack->maxElementCount);
    }
}