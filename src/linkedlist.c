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
    ListNode *nptr = pList->headerNode.pLink;
    return nptr;
}

ListNode* getLLNthNode(LinkedList* pList, int position) {
    ListNode* ln = pList->headerNode.pLink;
    printf("ln ptr = %p\n", ln);
    for (int i = 0; i < position; i++) {
        ln = ln->pLink;
        printf("position [%d] | i [%d] | ln ptr = %p\n", position, i, ln);
    }
    return ln;
}

ListNode* getLLLastNode(LinkedList* pList) {
    return getLLNthNode(pList, pList->currentElementCount - 1);
}


int addLLElement(LinkedList* pList, int position, ListNode element) {
    if (isValidPosition(pList, position, FLAG_ADD) == FALSE)
        return FALSE;
    if (position == 0 || position == pList->currentElementCount) {
        ListNode *nptr = pList->headerNode.pLink;
        while (nptr->pLink != NULL) {
            nptr = nptr->pLink;
        }
        *nptr = element;
        pList->currentElementCount++;
        return TRUE;
    } else {
        ListNode *prev_nptr = getLLNthNode(pList, position);
        ListNode *next_nptr = getLLNthNode(pList, position + 1);
        prev_nptr->pLink = &element;
        element.pLink = next_nptr;
        pList->currentElementCount++;
        return TRUE;
    }
}

int addLLData(LinkedList* pList, int position, int data) {
    if (isValidPosition(pList, position, FLAG_ADD) == FALSE)
        return FALSE;
    if (position == 0 || position == pList->currentElementCount) {
        ListNode *nptr = pList->headerNode.pLink;
        while (nptr->pLink != NULL) {
            nptr = nptr->pLink;
        }
        nptr = createListNode(data);
        pList->currentElementCount++;
        return TRUE;
    } else {
        ListNode *prev_nptr = getLLNthNode(pList, position);
        ListNode *next_nptr = getLLNthNode(pList, position + 1);
        prev_nptr->pLink = createListNode(data);
        prev_nptr->pLink->pLink = next_nptr;
        pList->currentElementCount++;
        return TRUE;
    }
}

