#include "./includes/linkedstack.h"
#include "./includes/darraystack.h"
#include "./includes/farraystack.h"
#include <stdio.h>
#include <string.h>

void testSpace_DynamicArrayStack(char *argv) {
    DynamicArrayStack *das = createDynamicArrayStack(3);

    for (size_t i = 0; i < strlen(argv); i++) {
        DASNode *nptr = createDASNode(argv[i]);
        pushDAS(das, *nptr);
        free(nptr);
    }
    displayDynamicArrayStack(das);
    for (size_t i = 0; i < strlen(argv) / 2; i++) {
        DASNode *nptr = popDAS(das);
        displayDynamicArrayStack(das);
        printf("popped_value = %c\n", nptr->data);
        free(nptr);
    }
    deleteDynamicArrayStack(das);
    system("leaks test");
}

void testSpace_LinkedStack(char *argv) {
    LinkedStack *ls = createLinkedStack(3);
    for (size_t i = 0; i < strlen(argv); i++) {
        StackNode *nptr = createLinkedStackNode(argv[i]);
        pushLS(ls, *nptr);
        free(nptr);
    }
    displayLinkedStack(ls);
    for (size_t i = 0; i < strlen(argv); i++) {
        StackNode *nptr = popLS(ls);
        printf("popped_value = %c\n", nptr->data);
        free(nptr);
    }
    deleteLinkedStack(ls);
    system("leaks test");
}

void testSpace_FixedArrayStack(char *argv) {
    FixedArrayStack *fas = createFixedArrayStack(10);
    for (size_t i = 0; i < strlen(argv); i++) {
        FASNode *nptr = createFASNode(argv[i]);
        pushFAS(fas, *nptr);
        free(nptr);
    }
    displayFixedArrayStack(fas);
    size_t limit = fas->currentElementCount;
    for (size_t i = 0; i < limit - 1; i++) {
        FASNode *nptr = popFAS(fas);
        displayFixedArrayStack(fas);
        printf("popped_value = %c\n", nptr->data);
        free(nptr);
    }
    deleteFixedArrayStack(fas);
    system("leaks test");
}

int main(int argc, char **argv) {
    if (argc != 2) return 0;
    printf("inserted input : [%s] :)\n", argv[1]);
    // testSpace_LinkedStack(argv[1]);
    // testSpace_DynamicArrayStack(argv[1]);
    testSpace_FixedArrayStack(argv[1]);
    return 0;
}