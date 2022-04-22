
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

static int isValidPosition(ArrayList* pList, int position, int flag) {
    if (flag & FLAG_ADD) {
        return pList->currentElementCount < position || position < 0 ? FALSE : TRUE;
    }
    if (flag & FLAG_OTHER){
        return pList->currentElementCount <= position || position < 0 ? FALSE : TRUE;
    }
    return FALSE;
}

int isArrayListFull(ArrayList *pList) {
    return pList->maxElementCount == pList->currentElementCount ? TRUE : FALSE;
}


int addALElement(ArrayList* pList, int position, ArrayListNode element) {
    if (isArrayListFull(pList) == TRUE
        || isValidPosition(pList, position, FLAG_ADD) == FALSE)
        return FALSE;
    if (position == pList->currentElementCount)
    {
        pList->pElement[position].data = element.data;
        pList->currentElementCount++;
    } else {
        for (int i = pList->currentElementCount; i >= position; i--) {
            pList->pElement[i + 1].data = pList->pElement[i].data;
        }
        pList->pElement[position].data = element.data;
        pList->currentElementCount++;
    }
    return TRUE;
}

int addALData(ArrayList* pList, int position, int data) {
    if (isArrayListFull(pList) == TRUE
        || isValidPosition(pList, position, FLAG_ADD) == FALSE)
        return FALSE;
    if (position == pList->currentElementCount)
    {
        pList->pElement[position].data = data;
        pList->currentElementCount++;
    } else {
        for (int i = pList->currentElementCount; i >= position; i--) {
            pList->pElement[i + 1].data = pList->pElement[i].data;
        }
        pList->pElement[position].data = data;
        pList->currentElementCount++;
    }
    return TRUE;
}

int removeALElement(ArrayList* pList, int position) {
    ArrayListNode *nptr = pList->pElement;
    if (isValidPosition(pList, position, FLAG_OTHER) == FALSE)
        return FALSE;
    int i = position;
    while (i < pList->currentElementCount - 1) {
        nptr[i].data = nptr[i + 1].data;
        i++;
    }
    nptr[i].data = 0;
    pList->currentElementCount--;
    return TRUE;
}

ArrayListNode* getALElement(ArrayList* pList, int position) {
    if (isValidPosition(pList, position, FLAG_OTHER) == FALSE)
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
    }
    pList->currentElementCount = 0;
}

int getArrayListLength(ArrayList* pList) {
    return pList->currentElementCount;
}


