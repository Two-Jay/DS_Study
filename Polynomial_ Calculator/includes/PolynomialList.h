#ifndef _PolynomialList_
#define _PolynomialList_

typedef struct  PolynomialListNodeType
{
	int Coefficient;
    int degree;
	int sign; // 1 or -1
    char character;
	struct PolynomialListNodeType* pLLink;
	struct PolynomialListNodeType* pRLink;
}               PolynomialListNode;

typedef struct PolynomialListType
{
	int	currentElementCount;		// ���� ����� ������ ����
	PolynomialListNode	*headerNode;		// ��� ���(Header Node)
} PolynomialList;

PolynomialList* createPolynomialList(void);
void deletePolynomialList(PolynomialList* pList);
int addPLElement(PolynomialList* pList, int position, PolynomialListNode *element);
int removePLElement(PolynomialList* pList, int position);
void clearPolynomialList(PolynomialList* pList);
int getPolynomialListLength(PolynomialList* pList);
PolynomialListNode* getPLElement(PolynomialList* pList, int position);
void displayPolynomialList(PolynomialList* pList);
PolynomialListNode *createPolynomialNode(int Coefficient, int degree, char character);
PolynomialListNode *mergePolynomialNode(PolynomialListNode* a, PolynomialListNode* b);
PolynomialListNode* copyPolynomialListNode(PolynomialListNode *other);

int removePLEByDegree(PolynomialList* pList, int degree);
PolynomialListNode* getPLElementByDegree(PolynomialList* pList, int degree);
//int sortbydegree(PolynomialList* pList);


#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0
#define FLAG_ADD	2
#define FLAG_OTHER	4
#define NONE_CHARACTER ' '

#endif // _PolynomialList_