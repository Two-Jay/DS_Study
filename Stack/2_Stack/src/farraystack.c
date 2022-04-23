#include "../includes/farraystack.h"
#include <stdlib.h>
#include <stdio.h>

FixedArrayStack* createFixedArrayStack(size_t init_size) {
    FixedArrayStack *ret = (FixedArrayStack *)calloc(sizeof(FixedArrayStack), 1);
    if (!ret) return NULL;
    ret->maxElementCount = init_size;
    ret->pElements = (FASNode *)calloc(sizeof(FASNode), ret->maxElementCount);
    if (!ret->pElements) {
        free(ret);
        return NULL;
    }
    return ret;
}

FASNode *createFASNode(char input) {
    FASNode *ret = (FASNode *)calloc(sizeof(FASNode), 1);
    if (!ret) return NULL;
    ret->data = input;
    return ret;
}

int pushFAS(FixedArrayStack* pStack, FASNode element) {
    if (isFixedArrayStackFull(pStack) == TRUE) {
        printf("pushLS : the Stack is fulled.\n");
        return FALSE;
    }
    pStack->pElements[pStack->currentElementCount].data = element.data;
    pStack->currentElementCount++;
    return TRUE;
}

FASNode* popFAS(FixedArrayStack* pStack) {
    if (isFixedArrayStackEmpty(pStack) == TRUE) return NULL;
    FASNode *currentTopNode = peekFAS(pStack);
    FASNode *ret = createFASNode(currentTopNode->data);
    if (!ret) return NULL;
    currentTopNode->data = 0;
    pStack->currentElementCount--;
    return ret;
};

FASNode* peekFAS(FixedArrayStack* pStack) {
    return pStack->currentElementCount == 0
        ? NULL : &(pStack->pElements[pStack->currentElementCount - 1]);
}

void deleteFixedArrayStack(FixedArrayStack* pStack) {
    free(pStack->pElements);
    free(pStack);
}


int isFixedArrayStackFull(FixedArrayStack* pStack) {
    return pStack->currentElementCount == pStack->maxElementCount ? TRUE : FALSE;
}

int isFixedArrayStackEmpty(FixedArrayStack* pStack) {
    return pStack->currentElementCount == 0 ? TRUE : FALSE;
}

void displayFixedArrayStack(FixedArrayStack *pStack) {
    if (!pStack) return ;
    printf("==================================\n");
    if (pStack->currentElementCount == 0) {
        printf("Stack_Top_Value : None\nStack_Current_Size : %zu\nStack_Max_Size : %zu\n",
            pStack->currentElementCount,
            pStack->maxElementCount);
    } else {
        printf("Stack_Top_Value : %c\nStack_Current_Size : %zu\nStack_Max_Size : %zu\n",
            peekFAS(pStack)->data,
            pStack->currentElementCount,
            pStack->maxElementCount);
    }
}