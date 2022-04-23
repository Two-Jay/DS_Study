#ifndef _FIXED_ARRAY_STACK_
#define _FIXED_ARRAY_STACK_

#include <stdlib.h>

typedef struct FixedArrayStackNodeType {
	char data;
} FASNode;

typedef struct FixedArrayStackType
{
	size_t currentElementCount;
    size_t maxElementCount;
	FASNode* pElements;	
} FixedArrayStack;

FixedArrayStack* createFixedArrayStack(size_t init_size);
FASNode *createFASNode(char input);
int pushFAS(FixedArrayStack* pStack, FASNode element);
FASNode* popFAS(FixedArrayStack* pStack);
FASNode* peekFAS(FixedArrayStack* pStack);

void deleteFixedArrayStack(FixedArrayStack* pStack);
int isFixedArrayStackFull(FixedArrayStack* pStack);
int isFixedArrayStackEmpty(FixedArrayStack* pStack);
void displayFixedArrayStack(FixedArrayStack *pStack);
#endif // _FIXED_ARRAY_STACK_

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif// _COMMON_STACK_DEF_