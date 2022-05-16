#ifndef _BIN_TREE_
#define _BIN_TREE_

#include <stdlib.h>


typedef struct HeapTreeNodeType {
	char data;
	int visited;

	struct HeapTreeNodeType* pLeftChild;
	struct HeapTreeNodeType* pRightChild;
}	HeapTreeNode;

typedef struct HeapTreeType {
	struct HeapTreeNodeType* pRootNode;
}	HeapTree;

HeapTree* makeHeapTree(HeapTreeNode rootNode);
HeapTreeNode* getRootNodeHT(HeapTree* pHeapTree);
HeapTreeNode* insertLeftChildNodeHT(HeapTreeNode* pParentNode, HeapTreeNode element);
HeapTreeNode* insertRightChildNodeHT(HeapTreeNode* pParentNode, HeapTreeNode element);
HeapTreeNode* getLeftChildNodeHT(HeapTreeNode* pNode);
HeapTreeNode* getRightChildNodeHT(HeapTreeNode* pNode);
void deleteHeapTree(HeapTree* pHeapTree);
void deleteHeapTreeNode(HeapTreeNode* pNode);

#endif

#ifndef _COMMON_TREE_DEF_
#define _COMMON_TREE_DEF_

#define TRUE		1
#define FALSE		0

#endif