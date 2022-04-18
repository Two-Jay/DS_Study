#include "./includes/arraylist.h"
#include "./includes/linkedlist.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_SMALL_MAX 10
#define TEST_SMALL_ZERO 0

void test_printAllAL(ArrayList *al) {
    printf("====================\n");
    for (int i = 0; i < al->maxElementCount; i++) {
        printf("%d ", al->pElement[i].data);
    }
    printf("\n");
    printf("is Array full ? : %s\n", isArrayListFull(al) ? "true" : "false");
    printf("max : %d\ncurrent : %d\n", al->maxElementCount, al->currentElementCount);
}

void test_printAllLL(LinkedList *ll) {
    if (!ll)
    {
        printf("there is no ll.....");
        return ;
    }
    printf("====================\n");
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
    printf("current : %d\n", ll->currentElementCount);
}

int array_test_main(void)
{
    ArrayList *al = createArrayList(TEST_SMALL_MAX);
    test_printAllAL(al);
    for (int i = 0; i < TEST_SMALL_MAX; i++) {
        addALData(al, 0, i + 5);
    }
    test_printAllAL(al);
    // clearArrayList(al);
    system("leaks test");
    return 0;
}

int linked_test_main(void)
{
    LinkedList *ll = createLinkedList();
    for (int i = 0; i < TEST_SMALL_MAX; i++) {
        addLLData(ll, i, i + 5);
    }
    deleteLinkedList(ll);
    test_printAllLL(ll);
    system("leaks test");
    return 0;
}

int main(void)
{
    linked_test_main();
    return 0;
}