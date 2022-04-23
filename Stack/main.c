#include "../includes/ALStack.h"
#include "../includes/LLStack.h"

void testSpaceLLStack(void) {

}

void testSpaceALStack(void) {
    ALStackBucket *als = createALStackBucket(3);
    
    pushALStackData(als, 10);
    pushALStackData(als, 20);
    pushALStackData(als, 30);
    displayALStack(als);
    pushALStackData(als, 40);
    displayALStack(als);
    deleteALStack(als);
}

int main(void) {
    // testSpaceALStack();
    testSpaceLLStack();
    system("leaks test");
    return 0;
}