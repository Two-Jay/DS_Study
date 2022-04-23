
#ifndef ALSTACK_H
#define ALSTACK_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct ALStackNodeType {
    int data_;
}   ALStackNode;

typedef struct ALStackBucketType {
    ALStackNode *sl_;
    size_t      currentElementCount_;
    size_t      maxSize_;
}   ALStackBucket;

ALStackBucket *createALStackBucket(size_t init_size);
ALStackNode *createALStackNode(int data);
bool    clearALStack(ALStackBucket *sBucket);
bool    deleteALStack(ALStackBucket *sBucket);
int     peakStackTopData(ALStackBucket *sBucket);
ALStackNode* peakStackTopNode(ALStackBucket *sBucket);
int     popStackTopData(ALStackBucket *sBucket);
ALStackNode* popStackTopNode(ALStackBucket *sBucket);
bool    pushALStackData(ALStackBucket *sBucket, int data);
bool    pushALStackElement(ALStackBucket *sBucket, ALStackNode *element);
size_t  getALStackSize(ALStackBucket *sBucket);
void    displayALStack(ALStackBucket *sBucket);

bool    resizeALStack(ALStackBucket *sBucket, size_t wanted_size);

#endif // ALSTACK_H
