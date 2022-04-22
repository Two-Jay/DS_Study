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

PolynomialListNode* copyPolynomialListNode(PolynomialListNode *other) {
    PolynomialListNode *ret = (PolynomialListNode *)calloc(sizeof(PolynomialListNode), 1);
    ret->Coefficient = other->Coefficient;
    ret->character = other->character; 
    ret->sign = other->sign;
    ret->degree = other->degree;
    return ret;
}

PolynomialListNode *createPolynomialNode(int Coefficient, int degree, char character) {
    PolynomialListNode *ret = (PolynomialListNode *)calloc(sizeof(PolynomialListNode), 1);
    if (!ret) return NULL;
    ret->Coefficient = Coefficient;
    ret->sign = 1;
    if (Coefficient < 0) {
        ret->Coefficient *= -1;
        ret->sign = -1;
    }
    ret->degree = degree;
    ret->character = character;
    return ret;
}

PolynomialListNode *mergePolynomialNode(PolynomialListNode* a, PolynomialListNode* b) {
    if (a->character != b->character) return FALSE;
    PolynomialListNode *ret = copyPolynomialListNode(a);
    if (b->sign == -1)  ret->Coefficient = ret->Coefficient - b->Coefficient;
    if (ret->Coefficient < 0) {
        ret->Coefficient *= -1;
        ret->sign = -1;
    }
    return ret;
}

PolynomialListNode* getDLLLastNode(PolynomialList* pList) {
    PolynomialListNode *nptr = pList->headerNode;
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

PolynomialListNode* getPLElement(PolynomialList* pList, int position) {
    PolynomialListNode *nptr = pList->headerNode;
    for (int i = 0; i < position; i++) {
        nptr = nptr->pRLink;
    }
    return nptr;
}

PolynomialListNode* getPLElementByDegree(PolynomialList* pList, int degree) {
    PolynomialListNode *nptr = pList->headerNode;
    for (int i = 0; i < pList->currentElementCount; i++) {
        if (nptr->degree == degree) return nptr;
        nptr = nptr->pRLink;
    }
    return nptr->degree == degree ? nptr : NULL;
}


int getPolynomialListLength(PolynomialList *pList) {
    return pList->currentElementCount;
}

int addPLElement(PolynomialList* pList, int position, PolynomialListNode *element) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (pList->currentElementCount == 0) {
        pList->headerNode = element;
        element->pRLink = pList->headerNode;
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
    return FALSE;
}

int removePLElement(PolynomialList* pList, int position) {
    if (isValidPosition(pList, position) == FALSE) return FALSE;
    if (position == 1) {
        PolynomialListNode *nptr = pList->headerNode;
        free(nptr);
        nptr = NULL;
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

int removePLElementByNodePTR(PolynomialList* pList, PolynomialListNode* nptr) {
    if (nptr) {
        PolynomialListNode *prev_nptr = nptr->pLLink;
        PolynomialListNode *next_nptr = nptr->pRLink;
        free(nptr);
        prev_nptr->pRLink = next_nptr;
        next_nptr->pLLink = prev_nptr;
        pList->currentElementCount--;
        return TRUE;
    }
    return FALSE;
};

int removePLEByDegree(PolynomialList* pList, int degree) {
    PolynomialListNode *nptr = getPLElementByDegree(pList, degree);
    return removePLElementByNodePTR(pList, nptr);
}


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
    PolynomialListNode *nptr = pList->headerNode;
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
        printf("[%d%c^%d] ", nptr->Coefficient, nptr->character, nptr->degree);
    }
    printf("\n");
}