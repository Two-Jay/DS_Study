#ifndef _DYNAMIC_ARRAY_STACK_
#define _DYNAMIC_ARRAY_STACK_

#include <stdlib.h>

typedef struct DynamicArrayStackNodeType {
	char data;
} DASNode;

typedef struct DynamicArrayStackType
{
	size_t currentElementCount;
    size_t maxElementCount;
	DASNode* pElements;
} DynamicArrayStack;

DynamicArrayStack* createDynamicArrayStack();
int pushDAS(DynamicArrayStack* pStack, DASNode element);
DASNode* popDAS(DynamicArrayStack* pStack);
DASNode* peekDAS(DynamicArrayStack* pStack);
void deleteDynamicArrayStack(DynamicArrayStack* pStack);
int isDynamicArrayStackFull(DynamicArrayStack* pStack);
int isDynamicArrayStackEmpty(DynamicArrayStack* pStack);

int resizeDynamicArrayStack(DynamicArrayStack* pStack, size_t wanted_size);
DASNode *createDASNode(char input);
void displayDynamicArrayStack(DynamicArrayStack *pStack);

#endif // _DYNAMIC_Array_STACK_

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif// _COMMON_STACK_DEF_