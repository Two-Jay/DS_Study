#include <stdio.h>
#include <stdlib.h>
#include "../includes/linkedlist.h"

static int isValidPosition(LinkedList* pList, int position, int flag) {
    if (flag & FLAG_ADD) {
        return pList->currentElementCount < position || position < 0 ? FALSE : TRUE;
    }
    if (flag & FLAG_OTHER){
        return pList->currentElementCount <= position || position < 0 ? FALSE : TRUE;
    }
    return FALSE;
}

LinkedList* createLinkedList() {
    LinkedList *ll;
    
    ll = (LinkedList *)calloc(sizeof(LinkedList), 1);
    if (!ll)
        return NULL;
     
    return ll;
}

ListNode *createListNode(int data) {
    ListNode *ln;
    ln = (ListNode *)malloc(sizeof(ListNode));
    if (!ln)
        return NULL;
    ln->data = data ? data : 0;
    ln->pLink = NULL;
    return ln;
}

ListNode* getLLElement(LinkedList* pList, int position) {
    if (position >= pList->currentElementCount)
        return NULL;
    ListNode *nptr = &(pList->headerNode);
    for (int i = 0;i < position;i++) {
        nptr = nptr->pLink;
    }
    return nptr;
}

ListNode* getLLLastNode(LinkedList* pList) {
    ListNode *nptr = &(pList->headerNode);
    while (nptr->pLink != NULL) {
        nptr = nptr->pLink;
    }
    return nptr;
}

int addLLElement(LinkedList* pList, int position, ListNode element) {
    if (isValidPosition(pList, position, FLAG_ADD) == FALSE)
        return FALSE;

    if (pList->currentElementCount == position) {
        ListNode *ln = getLLLastNode(pList);
        ln->pLink = &element;
        pList->currentElementCount++;
    } else {
        ListNode *prev_ln = getLLElement(pList, position - 1);
        ListNode *next_ln = prev_ln->pLink;
        prev_ln->pLink = &element;
        pList->currentElementCount++;
        prev_ln->pLink->pLink = next_ln;
    }
    return TRUE;
}

int addLLData(LinkedList* pList, int position, int data) {
    if (isValidPosition(pList, position, FLAG_ADD) == FALSE)
        return FALSE;
    if (pList->currentElementCount == position) {
        ListNode *ln = getLLLastNode(pList);
        ln->pLink = createListNode(data);
        pList->currentElementCount++;
    } else {
        ListNode *prev_ln = getLLElement(pList, position - 1);
        ListNode *next_ln = prev_ln->pLink;
        prev_ln->pLink = createListNode(data);
        pList->currentElementCount++;
        prev_ln->pLink->pLink = next_ln;
    }
    return TRUE;
}

int getLinkedListLength(LinkedList* pList) {
    return pList->currentElementCount;
}

int removeLLElement(LinkedList* pList, int position) {
    if (isValidPosition(pList, position, FLAG_OTHER) == FALSE)
        return FALSE;
    if (pList->currentElementCount - 1 == position) {
        ListNode *ln = getLLElement(pList, position);
        free(ln->pLink);
        ln->pLink = NULL;
        pList->currentElementCount--;
    } else {
        ListNode *prev_ln = getLLElement(pList, position - 1);
        ListNode *next_ln = prev_ln->pLink->pLink;
        free(prev_ln->pLink);
        pList->currentElementCount--;
        prev_ln->pLink = next_ln;
    }
    return TRUE;
}

void clearLinkedList(LinkedList* pList) {
    if (pList->currentElementCount == 0)
        return ;
    for (int i = pList->currentElementCount; i >= 0; i--) {
        removeLLElement(pList, i);
    }
};

void deleteLinkedList(LinkedList* pList) {
    clearLinkedList(pList);
    free(pList);
    pList = NULL;
};