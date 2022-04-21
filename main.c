// #include "./includes/arraylist.h"
// #include "./includes/linkedlist.h"
#include "./includes/doublylist.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_LENGTH 10

void DLE_test_main(void) {
    DoublyList *dll = createDoublyList();
    for (int i = 0; i < TEST_LENGTH; i++) {
        addDLElement(dll, i, createDoublyNode(i + 10));
    }
    displayDoublyList(dll);
    clearDoublyList(dll);
}

int main(void)
{
    DLE_test_main();
    return 0;
}