#include "./includes/arraylist.h"
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

int main(void)
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