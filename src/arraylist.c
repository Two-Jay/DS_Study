
#include "../includes/arraylist.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

ArrayList* createArrayList(int maxElementCount) {
    if (maxElementCount < 0) {
        return NULL;
    }
    ArrayList *al = (ArrayList *)malloc(sizeof(ArrayList));
    if (!al) {
        return NULL;
    }
    al->maxElementCount = maxElementCount;
    al->currentElementCount = 0;
    al->pElement = (ArrayListNode *)calloc(sizeof(ArrayListNode), maxElementCount);
    if (!al->pElement) {
        free(al);
        return NULL; 
    }
    return al;
}

void deleteArrayList(ArrayList *pList) {
    free(pList->pElement);
    free(pList);
}

int isArrayListFull(ArrayList *pList) {
    return pList->maxElementCount == pList->currentElementCount ? TRUE : FALSE;
}

int isArrayNodeAssigned(ArrayList *pList, int position) {
    return pList->pElement[position].isAssigned == TRUE ? TRUE : FALSE;
}

int addALElement(ArrayList* pList, int position, ArrayListNode element) {
    if (isArrayListFull(pList) == TRUE ||
        position > pList->currentElementCount)
        return FALSE;
    pList->pElement[position].data = element.data;
    pList->pElement[position].isAssigned = TRUE;
    pList->currentElementCount++;
    return TRUE;
}

int addALData(ArrayList* pList, int position, int data) {
    if (isArrayListFull(pList) == TRUE ||
        position > pList->currentElementCount)
        return FALSE;
    pList->pElement[position].data = data;
    pList->pElement[position].isAssigned = TRUE;
    pList->currentElementCount++;
    return TRUE;
}

// int removeALElement(ArrayList* pList, int position) {
    
// }

ArrayListNode* getALElement(ArrayList* pList, int position) {
    // assign
    if (position < 0 || pList->currentElementCount <= position)
        return NULL;
    return &pList->pElement[position];
}

void displayArrayList(ArrayList* pList) {
    printf("[");
    for (int i = 0; i < pList->currentElementCount;i++) {
        ArrayListNode* nptr = getALElement(pList, i);
        if (i == pList->currentElementCount - 1)
            printf(" %d ", nptr->data);
        else
            printf(" %d,", nptr->data);
    }
    printf("]\n");
}

void clearArrayList(ArrayList *pList) {
    ArrayListNode *nptr;
    for (int i = 0; i < pList->currentElementCount; i++) {
        nptr = getALElement(pList, i);
        nptr->data = 0;
        nptr->isAssigned = FALSE;
    }
    pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList) {
    return pList->currentElementCount;
}


