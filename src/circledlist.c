#include "../includes/circledlist.h"
#include <stdlib.h>
#include <stdio.h>

static int isValidPosition(CircledList *pList, int position) {
    return (pList->currentElementCount >= position || position > 0);
}

CircledList *createCircledList(void) {
    CircledList *ret = (CircledList *)calloc(sizeof(CircledList), 1);
    return ret ? ret : NULL;
};

CircledListNode *createCircledNode(int data) {
    CircledListNode *ret = (CircledListNode *)calloc(sizeof(CircledListNode), 1);
    if (!ret) return NULL;
    ret->data = data;
    return ret;
}

CircledListNode* getCLLastNode(CircledList* pList) {
    CircledListNode *nptr = pList->headerNodePtr;
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

CircledListNode* getCLElement(CircledList* pList, int position) {
    CircledListNode *nptr = pList->headerNodePtr;
    for (int i = 0; i < position; i++) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

int getCircledListLength(CircledList *pList) {
    return pList->currentElementCount;
}

int addCLElement(CircledList* pList, int position, CircledListNode *element) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (pList->currentElementCount == 0) {
        pList->headerNodePtr = element;
        element->pRLink = pList->headerNodePtr;
        pList->currentElementCount++;
        return TRUE;
    } else {
        CircledListNode *nptr = getCLElement(pList, position - 1);
        CircledListNode *nptr2 = nptr->pRLink;
        nptr->pRLink = element;
        nptr2->pLLink = element;
        element->pLLink = nptr;
        element->pRLink = nptr2;
        pList->currentElementCount++;
        return TRUE;
    }
    return FALSE;
}

int removeCLElement(CircledList* pList, int position) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (position == 1) {
        CircledListNode *nptr = pList->headerNodePtr;
        free(nptr);
        nptr = NULL;
        pList->currentElementCount--;
        return TRUE;
    } else {
        CircledListNode *nptr = getCLElement(pList, position - 1);
        CircledListNode *nptr2 = nptr->pRLink->pRLink;
        free(nptr->pRLink);
        nptr->pRLink = nptr2;
        nptr2->pLLink = nptr;
        pList->currentElementCount--;
        return TRUE;
    }
};

void clearCircledList(CircledList* pList) {
    for (int i = pList->currentElementCount; i > 0; i--) {
        removeCLElement(pList, i + 1);
    }
}

void displayCircledList(CircledList* pList) {
    if (!pList) {
        printf("there is no ll.....");
        return ;
    }
    printf("====================\n");
    printf("current : %d\n", pList->currentElementCount);
    CircledListNode *nptr = pList->headerNodePtr;
    for (int i = 0; i < pList->currentElementCount; i++) {
        if (i < pList->currentElementCount - 1)
            printf("[%d] - ", nptr->data);
        else
            printf("[%d]\n", nptr->data);
        nptr = nptr->pRLink;
    }
}

void deleteCircledList(CircledList* pList) {
    if (pList->headerNodePtr)
        clearCircledList(pList);
    free(pList);
}