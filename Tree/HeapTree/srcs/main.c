#include "../includes/treeTester.h"

#define TEST_SMALL_MAX 10

void testfield(void) {
    HeapBucket *ph = createHeap(5);
    for (int i = 1; i <= TEST_SMALL_MAX; i++) {
        addMaxHeapElement(ph, i * 10);        
    }
    printHeapArray(ph);
    for (int i = 0; i < 3; i++) {
        printf("removed : %d\n", deleteMaxHeapElement(ph));
        printHeapArray(ph);
    }
    deleteHeap(ph);
    system("leaks heap");
}

int main(void) {
    testfield();
    return 0;
}