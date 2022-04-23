
#ifndef LLSTACK_H
#define LLSTACK_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct LLStackNodeType {
    int data_;
    LLStackNode *prevLink_;
    LLStackNode *nextLink_;    
}   LLStackNode;

typedef struct LLStackBucketType {
    LLStackNode *headerNodePtr_;
    size_t      currentElementCount_;
}   LLStackBucket;

LLStackBucket   *createLLStackBucket(void);
LLStackNode     *createLLStackNode(int data);

int     peakTopData(LLStackBucket *sBucket);
LLStackNode* peakTopNode(LLStackBucket *sBucket);
int     popStackTopData(LLStackBucket *sBucket);
LLStackNode* popStackTopNode(LLStackBucket *sBucket);
bool    pushLLStackData(LLStackBucket *sBucket, int data);
bool    pushLLStackElement(LLStackBucket *sBucket, LLStackNode *element);

size_t  getLLStackSize(LLStackBucket *sBucket);
bool    clearLLStack(LLStackBucket *sBucket);
bool    deleteLLStack(LLStackBucket *sBucket);
void    displayLLStack(LLStackBucket *sBucket);

#endif // LLSTACK_H
