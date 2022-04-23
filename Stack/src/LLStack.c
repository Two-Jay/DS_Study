#include "../includes/LLStack.h"

LLStackBucket   *createLLStackBucket(void) {
    LLStackBucket *ret = (LLStackBucket *)calloc(sizeof(LLStackBucket), 1);
    if (!ret) return NULL;
    return ret;
}

LLStackNode     *createLLStackNode(int data) {
    LLStackNode *ret = (LLStackNode *)calloc(sizeof(LLStackNode), 1);
    if (!ret) return NULL;
    ret->data_ = data;
    return ret;
}

bool    removeLLStackNode(LLStackBucket *sBucket) {

}

static LLStackNode *getLLStackTopNodePtr(LLStackBucket *sBucket) {
    LLStackNode *nptr = sBucket->headerNodePtr_;
    if ()
}

int     peakTopData(LLStackBucket *sBucket) {
    return sBucket->currentElementCount_ == 0 ? 0 : getLLStackTopNodePtr(sBucket)->data_;
}

LLStackNode* peakTopNode(LLStackBucket *sBucket) {
    return getLLStackTopNodePtr(sBucket);
}

int     popStackTopData(LLStackBucket *sBucket) {

}

LLStackNode* popStackTopNode(LLStackBucket *sBucket) {

}

bool    pushLLStackData(LLStackBucket *sBucket, int data) {

}

bool    pushLLStackElement(LLStackBucket *sBucket, LLStackNode *element) {

}

size_t  getLLStackSize(LLStackBucket *sBucket) {
    return sBucket->currentElementCount_;
}

bool    clearLLStack(LLStackBucket *sBucket) {

}

bool    deleteLLStack(LLStackBucket *sBucket) {

}

void    displayLLStack(LLStackBucket *sBucket) {

}
