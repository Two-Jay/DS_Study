#ifndef _PolynomialList_
#define _PolynomialList_

typedef struct  PolynomialListNodeType
{
	int Coefficient;
    int degree;
    char character;
	struct PolynomialListNodeType* pLLink;
	struct PolynomialListNodeType* pRLink;
}               PolynomialListNode;

typedef struct PolynomialListType
{
	int	currentElementCount;		// ���� ����� ������ ����
	PolynomialListNode	headerNode;		// ��� ���(Header Node)
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

#endif

#ifndef _COMMON_LIST_DEF_
#define _COMMON_LIST_DEF_

#define TRUE		1
#define FALSE		0
#define FLAG_ADD	2
#define FLAG_OTHER	4

#endif // _PolynomialList_