#include "./includes/arraylist.h"
#include <stdio.h>
#include <stdlib.h>

#define TEST_SMALL_MAX 10
#define TEST_SMALL_ZERO 0

void test_printAllAL(ArrayList *al) {
    for (int i = 0; i < al->maxElementCount; i++) {
        printf("%d ", al->pElement[i].data);
    }
    printf("\n");
}

int main(void)
{
    ArrayList *al = createArrayList(TEST_SMALL_MAX);
    printf("max : %d\ncurrent : %d\n", al->maxElementCount, al->currentElementCount);
    printf("%d\n", isArrayListFull(al));
    for (int i = 0; i < TEST_SMALL_MAX; i++) {
        addALData(al, i, i + 5);
    }
    printf("Length : %d\n", getArrayListLength(al));    
    removeALElement(al, 9);
    test_printAllAL(al);
    printf("Length : %d\n", getArrayListLength(al));
    removeALElement(al, 5);
    test_printAllAL(al);
    printf("Length : %d\n", getArrayListLength(al));
    removeALElement(al, 0);
    test_printAllAL(al);
    printf("Length : %d\n", getArrayListLength(al));
    // clearArrayList(al);
    system("leaks test");
    return 0;
}