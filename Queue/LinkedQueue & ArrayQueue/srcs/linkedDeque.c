#include "../includes/linkeddeque.h"
#include <stdlib.h>
#include <stdio.h>

LinkedDeque* createLinkedDeque() {
    LinkedDeque *ret = (LinkedDeque *)calloc(sizeof(LinkedDeque), 1);
    return !ret ? NULL : ret;
};

DequeNode* createLDNode(char input) {
    DequeNode *ret = (DequeNode *)calloc(sizeof(DequeNode), 1);
    if (ret) ret->data = input;
    return ret;
};

int insertFrontLD(LinkedDeque* pDeque, DequeNode element) {
    DequeNode *pNewNode = createLDNode(element.data);
    if (isLinkedDequeEmpty(pDeque) == TRUE) {
        pDeque->pFrontNode = pNewNode;
        pDeque->pRearNode = pNewNode;
        pDeque->currentElementCount++;
        return TRUE;
    } else {
        pNewNode->pRLink = pDeque->pFrontNode;
        pDeque->pFrontNode->pLLink = pNewNode;
        pDeque->pFrontNode = pNewNode;
        pDeque->currentElementCount++;
        return TRUE;
    }
};

int insertRearLD(LinkedDeque* pDeque, DequeNode element) {
    DequeNode *pNewNode = createLDNode(element.data);
    if (isLinkedDequeEmpty(pDeque) == TRUE) {
        pDeque->pFrontNode = pNewNode;
        pDeque->pRearNode = pNewNode;
        pDeque->currentElementCount++;
        return TRUE;
    } else {
        pNewNode->pLLink = pDeque->pRearNode;
        pDeque->pRearNode->pRLink = pNewNode;
        pDeque->pRearNode = pNewNode;
        pDeque->currentElementCount++;
        return TRUE;
    }
};

DequeNode* deleteFrontLD(LinkedDeque* pDeque) {
    DequeNode *nptr = peekFrontLD(pDeque);
    if (isLinkedDequeEmpty(pDeque) == TRUE) return NULL;
    if (pDeque->currentElementCount == 1) {
        pDeque->currentElementCount--;
        pDeque->pFrontNode = NULL;
        pDeque->pRearNode = NULL;
        return nptr;
    }
    pDeque->pFrontNode = nptr->pRLink;
    pDeque->pFrontNode->pLLink = NULL;
    pDeque->currentElementCount--;
    return nptr;
};

DequeNode* deleteRearLD(LinkedDeque* pDeque) {
    DequeNode *nptr = peekRearLD(pDeque);
    if (isLinkedDequeEmpty(pDeque) == TRUE) return NULL;
    if (pDeque->currentElementCount == 1) {
        pDeque->currentElementCount--;
        pDeque->pFrontNode = NULL;
        pDeque->pRearNode = NULL;
        return nptr;
    }
    pDeque->pRearNode = nptr->pLLink;
    pDeque->pRearNode->pRLink = NULL;
    pDeque->currentElementCount--;
    return nptr;
};

DequeNode* peekFrontLD(LinkedDeque* pDeque) {
    return pDeque->pFrontNode;
};

DequeNode* peekRearLD(LinkedDeque* pDeque) {
    return pDeque->pRearNode;
};

int isLinkedDequeEmpty(LinkedDeque* pDeque) {
    return (pDeque->currentElementCount == 0);
};

void displayLD(LinkedDeque* pDeque) {
    DequeNode *fnptr = peekFrontLD(pDeque);
    DequeNode *rnptr = peekRearLD(pDeque);
    printf("--------------------------\n");
    printf("Deque의 현재 사이즈 : %d\nDeque의 현재 front의 값 : %c\nDeque의 현재 rear의 값 : %c\n",
        pDeque->currentElementCount,
        fnptr ? fnptr->data : ' ',
        rnptr ? rnptr->data : ' ');
};

void deleteLinkedDeque(LinkedDeque* pDeque) {
    DequeNode *nptr = pDeque->pFrontNode;
    DequeNode *next;
    while (nptr) {
        next = nptr->pRLink ? nptr->pRLink : NULL;
        free(nptr);
        nptr = next;
    }
    free(pDeque);
};