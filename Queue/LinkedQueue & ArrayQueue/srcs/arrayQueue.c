#include "../includes/arrayqueue.h"
#include <stdlib.h>
#include <stdio.h>

ArrayQueue* createArrayQueue(int maxElementCount) {
    ArrayQueue* ret = (ArrayQueue *)calloc(sizeof(ArrayQueue), 1);
    if (!ret) return NULL;
    ret->maxElementCount = maxElementCount;
    ret->front = -1;
    ret->rear = -1;
    ret->pElement = (ArrayQueueNode *)calloc(sizeof(ArrayQueueNode), maxElementCount);
    if (!ret->pElement) {
        free(ret);
        return NULL;
    }
    return ret;
};

ArrayQueueNode *createArrayQueueNode(char input) {
    ArrayQueueNode *ret = (ArrayQueueNode *)calloc(sizeof(ArrayQueueNode), 1);
    if (!ret) return NULL;
    ret->data = input;
    return ret;
}

int isArrayQueueFull(ArrayQueue* pQueue) {
    return (pQueue->currentElementCount == pQueue->maxElementCount);
};

int isArrayQueueEmpty(ArrayQueue* pQueue) {
    return (pQueue->currentElementCount == 0);
};

int enqueueAQ(ArrayQueue* pQueue, ArrayQueueNode element) {
    if (isArrayQueueFull(pQueue))
        return FALSE;
    pQueue->front = isArrayQueueEmpty(pQueue) ? 0 : pQueue->front;
    pQueue->rear = (pQueue->rear + 1) % pQueue->maxElementCount; 
    pQueue->pElement[pQueue->rear].data = element.data;
    pQueue->currentElementCount++;
    return TRUE;
};

// 실제로 데이터를 변경
// 빼내온 데이터를 반환해야함
// 그리고 길이도 낮춰줘야함
ArrayQueueNode *dequeueAQ(ArrayQueue* pQueue) {
    ArrayQueueNode *ret = createArrayQueueNode(peekAQ(pQueue)->data);
    peekAQ(pQueue)->data = 0;
    pQueue->front = (pQueue->front + 1) % pQueue->maxElementCount;
    pQueue->currentElementCount--;
    if (isArrayQueueEmpty(pQueue)) {
        pQueue->front = -1;
        pQueue->rear = -1;
    }
    return ret;
};

void displayArrayQueue(ArrayQueue* pQueue) {
    printf("--------------------------\n");
    printf("pQueue 현재 사이즈 : %d\npQueue 최대 사이즈 : %d\npQueue front 인덱스 : %d\npQueue rear 인덱스 : %d\npQueue 현재 peek의 data : %c\n",
        pQueue->currentElementCount,
        pQueue->maxElementCount,
        pQueue->front,
        pQueue->rear,
        isArrayQueueEmpty(pQueue) ? ' ' : peekAQ(pQueue)->data);
};

ArrayQueueNode *peekAQ(ArrayQueue* pQueue) {
    return isArrayQueueEmpty(pQueue) ? NULL : &(pQueue->pElement[pQueue->front]);
};

void deleteArrayQueue(ArrayQueue* pQueue) {
    free(pQueue->pElement);
    free(pQueue);
};