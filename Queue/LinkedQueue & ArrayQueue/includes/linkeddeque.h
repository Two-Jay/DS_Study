#ifndef _LINKED_DEQUE_
#define _LINKED_DEQUE_

typedef struct DequeNodeType
{
	char data;
	struct DequeNodeType* pRLink;
	struct DequeNodeType* pLLink;
} DequeNode;

typedef struct LinkedDequeType
{
	int currentElementCount;	// ���� ������ ����
	DequeNode* pFrontNode;		// Front ����� ������
	DequeNode* pRearNode;		// Rear ����� ������
} LinkedDeque;

LinkedDeque* createLinkedDeque();
DequeNode* createLDNode(char input);
int insertFrontLD(LinkedDeque* pDeque, DequeNode element);
int insertRearLD(LinkedDeque* pDeque, DequeNode element);
DequeNode* deleteFrontLD(LinkedDeque* pDeque);
DequeNode* deleteRearLD(LinkedDeque* pDeque);
DequeNode* peekFrontLD(LinkedDeque* pDeque);
DequeNode* peekRearLD(LinkedDeque* pDeque);
DequeNode* createLDNode(char input);
void deleteLinkedDeque(LinkedDeque* pDeque);
int isLinkedDequeFull(LinkedDeque* pDeque);
int isLinkedDequeEmpty(LinkedDeque* pDeque);
void displayLD(LinkedDeque* pDeque);

#endif

#ifndef _COMMON_QUEUE_DEF_
#define _COMMON_QUEUE_DEF_

#define TRUE		1
#define FALSE		0

#endif