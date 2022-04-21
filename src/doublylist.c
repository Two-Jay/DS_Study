#include "./includes/doublylist.h"
#include <stdlib.h>

static int isValidPosition(DoublyList *pList, int position, int flag) {
    if (flag & FLAG_ADD) {
        return (pList->currentElementCount < position || position < 0);
    }
    if (flag & FLAG_OTHER) {
        return (pList->currentElementCount <= position || position < 0);
    }
    return FALSE;
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

int getDoublyListLength(DoublyList *pList) {
    return pList->currentElementCount;
}

int addDLElement(DoublyList* pList, int position, DoublyListNode element) {
    if (isValidPosition(pList, position, FLAG_ADD) == FALSE) return FALSE;
    if (position == pList->currentElementCount) {
        DoublyListNode *nptr = getDLELastElement(pList);
        nptr->pRLink = &element;
        element.pLLink = nptr;
    }
}

DoublyListNode* getDLELastElement(DoublyList *pList) {
    DoublyListNode *nptr = &(pList->headerNode);
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

DoublyListNode* getDLElement(DoublyList* pList, int position) {
    DoublyListNode *nptr = &(pList->headerNode);    
    if (isValidPosition(pList, position, FLAG_OTHER) == FALSE) return NULL;
    for (int i = 0; i < position; i++) {
        nptr = nptr->pRLink;
    }
    return nptr;
}
