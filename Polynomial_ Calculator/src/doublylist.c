#include "../includes/PolynomialList.h"
#include <stdlib.h>
#include <stdio.h>

static int isValidPosition(PolynomialList *pList, int position) {
    return (pList->currentElementCount >= position || position > 0);
}

PolynomialList* createPolynomialList(void) {
    PolynomialList *ret = (PolynomialList *)calloc(sizeof(PolynomialList), 1);
    return !ret ? NULL : ret;
}

PolynomialListNode *createPolynomialNode(int Coefficient, int degree, char character) {
    PolynomialListNode *ret = (PolynomialListNode *)calloc(sizeof(PolynomialListNode), 1);
    if (!ret) return NULL;
    ret->Coefficient = Coefficient;
    ret->degree = degree;
    ret->character = character;
    return ret;
}

PolynomialListNode* getDLLLastNode(PolynomialList* pList) {
    PolynomialListNode *nptr = &(pList->headerNode);
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

PolynomialListNode* getPLElement(PolynomialList* pList, int position) {
    PolynomialListNode *nptr = &(pList->headerNode);
    for (int i = 0; i < position; i++) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

int getPolynomialListLength(PolynomialList *pList) {
    return pList->currentElementCount;
}

int addPLElement(PolynomialList* pList, int position, PolynomialListNode *element) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (position == pList->currentElementCount) {
        PolynomialListNode *nptr = getDLLLastNode(pList);
        nptr->pRLink = element;
        element->pLLink = nptr;
        pList->currentElementCount++;
        return TRUE;
    } else {
        PolynomialListNode *nptr = getPLElement(pList, position - 1);
        PolynomialListNode *nptr2 = nptr->pRLink;
        nptr->pRLink = element;
        nptr2->pLLink = element;
        element->pLLink = nptr;
        element->pRLink = nptr2;
        pList->currentElementCount++;
        return TRUE;
    }
}

int removePLElement(PolynomialList* pList, int position) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (position == pList->currentElementCount) {
        PolynomialListNode *nptr = getPLElement(pList, position - 1);
        free(nptr->pRLink);
        nptr->pRLink = NULL;
        pList->currentElementCount--;
        return TRUE;
    } else {
        PolynomialListNode *nptr = getPLElement(pList, position - 1);
        PolynomialListNode *nptr2 = nptr->pRLink->pRLink;
        free(nptr->pRLink);
        nptr->pRLink = nptr2;
        nptr2->pLLink = nptr;
        pList->currentElementCount--;
        return TRUE;
    }
};

void clearPolynomialList(PolynomialList* pList) {
    for (int i = pList->currentElementCount;i > 0; i--) {
        removePLElement(pList, i);
    }
};

void deletePolynomialList(PolynomialList* pList) {
    clearPolynomialList(pList);
    free(pList);
}

void displayPolynomialList(PolynomialList *pList) {
    if (!pList) {
        printf("there is no ll.....");
        return ;
    }
    printf("====================\n");
    printf("current : %d\n", pList->currentElementCount);
    PolynomialListNode *nptr = &(pList->headerNode);
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
        printf("[%d]", nptr->data);
    }
    printf("\n");
}