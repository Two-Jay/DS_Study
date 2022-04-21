#ifndef _CircledLIST_
#define _CircledLIST_

typedef struct	CircledListNodeType {
	int data;
	struct CircledListNodeType* pLLink;
	struct CircledListNodeType* pRLink;
}				CircledListNode;

typedef struct	CircledListType {
	int	currentElementCount;
	CircledListNodeType	*headerNodePtr;
}				CircledList;

CircledList* createCircledList();
void deleteCircledList(CircledList* pList);
int addDLElement(CircledList* pList, int position, CircledListNode *element);
int removeDLElement(CircledList* pList, int position);
void clearCircledList(CircledList* pList);
int getCircledListLength(CircledList* pList);
CircledListNode* getDLElement(CircledList* pList, int position);
void displayCircledList(CircledList* pList);
CircledListNode *createCircledNode(int data);

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0
#define FLAG_ADD	2
#define FLAG_OTHER	4

#endif