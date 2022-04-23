#ifndef _LINKED_STACK_
#define _LINKED_STACK_

#include <stdlib.h>

typedef struct StackNodeType
{
	char data;
	struct StackNodeType* pLink;
} StackNode;

typedef struct LinkedStackType
{
	size_t currentElementCount;
	size_t maxElementCount;
	StackNode* pTopElement;		
} LinkedStack;

LinkedStack* createLinkedStack();
int pushLS(LinkedStack* pStack, StackNode element);
StackNode* popLS(LinkedStack* pStack);
StackNode* peekLS(LinkedStack* pStack);
void deleteLinkedStack(LinkedStack* pStack);
int isLinkedStackFull(LinkedStack* pStack);
int isLinkedStackEmpty(LinkedStack* pStack);

void displayLinkedStack(LinkedStack *pStack);
StackNode* createLinkedStackNode(char data);

#endif // _LINKED_STACK_

#ifndef _COMMON_STACK_DEF_
#define _COMMON_STACK_DEF_

#define TRUE		1
#define FALSE		0

#endif // _LINKED_STACK_