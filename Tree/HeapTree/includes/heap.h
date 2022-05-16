#ifndef _HEAPTREE_
#define _HEAPTREE_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct HeapNodeType {
	int data;
	int visited;
}	HeapNode;

typedef struct HeapBucketType {
	struct	HeapNodeType* pHeapArray;
	size_t	size;
	size_t  capacity;
}	HeapBucket;

HeapBucket* createHeap(size_t capacity);
bool addMaxHeapElement(HeapBucket *pHeap, int data);
int deleteMaxHeapElement(HeapBucket* pHeap);
void deleteHeap(HeapBucket* pHeap);
size_t getSizeHeap(HeapBucket* pHeap);

bool isHeapEmpty(HeapBucket* pHeap);
bool isHeapFull(HeapBucket* pHeap);
bool reallocHeapArray(HeapBucket* pHeap);
void printHeapArray(HeapBucket *pHeap);

#endif