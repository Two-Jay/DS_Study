#include "../includes/tester.h"
#include "../includes/linkedlist.h"
#include <stdio.h>

void test_printAllLL(LinkedList *ll) {
    if (!ll) {
        printf("there is no ll.....");
        return ;
    }
    printf("====================\n");
    printf("current : %d\n", ll->currentElementCount);
    ListNode *nptr = &(ll->headerNode);
    for (int i = 0; i < ll->currentElementCount; i++) {
        nptr = nptr->pLink;
        if (i < ll->currentElementCount - 1) {
            printf("[%d] - ", nptr->data);
        }
        else 
            printf("[%d]", nptr->data);
    }
    printf("\n");
}

int linked_test_main(void)
{
    LinkedList *ll = createLinkedList();
    for (int i = 0; i < TEST_SMALL_MAX; i++) {
        ListNode *ln = createListNode(i + 5);
        addLLElement(ll, 0, *ln);
    }
    deleteLinkedList(ll);
    test_printAllLL(ll);
    system("leaks test");
    return 0;
}