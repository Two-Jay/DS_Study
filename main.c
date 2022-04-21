// #include "./includes/arraylist.h"
// #include "./includes/linkedlist.h"
#include "./includes/doublylist.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_LENGTH 10

void test_printAllDLE(DoublyList *dll) {
    if (!dll) {
        printf("there is no ll.....");
        return ;
    }
    printf("====================\n");
    printf("current : %d\n", dll->currentElementCount);
    DoublyListNode *nptr = &(dll->headerNode);
    while (nptr->pRLink != NULL) {
        nptr = nptr->pRLink;
        printf("[%d]", nptr->data);
    }
    printf("\n");
}

void DLE_test_main(void) {
    DoublyList *dll = createDoublyList();
    for (int i = 0; i < TEST_LENGTH; i++) {
        addDLElement(dll, i, createDoublyNode(i + 10));
    }
    for (int i = 0; i < 3; i++) {
        removeDLElement(dll, 3);
    }
    test_printAllDLE(dll);
}

int main(void)
{
    DLE_test_main();
    return 0;
}