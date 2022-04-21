// #include "./includes/arraylist.h"
// #include "./includes/linkedlist.h"
// #include "./includes/doublylist.h"
#include "./includes/circledlist.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_LENGTH 10

// void DLE_test_main(void) {
//     DoublyList *dll = createDoublyList();
//     for (int i = 0; i < TEST_LENGTH; i++) {
//         addDLElement(dll, i, createDoublyNode(i + 10));
//     }
//     displayDoublyList(dll);
//     clearDoublyList(dll);
// }

void CLE_test_main(void) {
    CircledList * cl = createCircledList();
    for (int i = 0; i < TEST_LENGTH; i++) {
        addCLElement(cl, i, createCircledNode(i + 10));
    }
    for (int i = 0; i < 3; i++) {
        removeCLElement(cl, 3);
    }
    displayCircledList(cl);
    clearCircledList(cl);
    displayCircledList(cl);
    deleteCircledList(cl);
    system("leaks test");
}

int main(void)
{
    // DLE_test_main();
    CLE_test_main();
    return 0;
}