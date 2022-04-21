#include "../includes/doublylist.h"
#include <stdlib.h>
#include <stdio.h>

static int isValidPosition(DoublyList *pList, int position) {
    return (pList->currentElementCount >= position || position > 0);
}

DoublyList* createDoublyList(void) {
    DoublyList *ret = (DoublyList *)calloc(sizeof(DoublyList), 1);
    return !ret ? NULL : ret;
}

DoublyListNode *createDoublyNode(int data) {
    DoublyListNode *ret = (DoublyListNode *)calloc(sizeof(DoublyListNode), 1);
    if (!ret) return NULL;
    ret->data = data;
    return ret;
}

DoublyListNode* getDLLLastNode(DoublyList* pList) {
    DoublyListNode *nptr = &(pList->headerNode);
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

DoublyListNode* getDLElement(DoublyList* pList, int position) {
    DoublyListNode *nptr = &(pList->headerNode);
    for (int i = 0; i < position; i++) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

int getDoublyListLength(DoublyList *pList) {
    return pList->currentElementCount;
}

int addDLElement(DoublyList* pList, int position, DoublyListNode *element) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (position == pList->currentElementCount) {
        DoublyListNode *nptr = getDLLLastNode(pList);
        nptr->pRLink = element;
        element->pLLink = nptr;
        pList->currentElementCount++;
        return TRUE;
    } else {
        DoublyListNode *nptr = getDLElement(pList, position - 1);
        DoublyListNode *nptr2 = nptr->pRLink;
        nptr->pRLink = element;
        nptr2->pLLink = element;
        element->pLLink = nptr;
        element->pRLink = nptr2;
        pList->currentElementCount++;
        return TRUE;
    }
}


