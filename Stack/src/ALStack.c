#include "../includes/ALStack.h"
#include <stdio.h>

ALStackBucket *createALStackBucket(size_t init_size) {
    ALStackBucket *ret = (ALStackBucket *)malloc(sizeof(ALStackBucket));
    if (!ret) return NULL;
    ret->maxSize_ = init_size;
    ret->sl_ = (ALStackNode *)calloc(sizeof(ALStackNode), init_size);
    ret->currentElementCount_ = 0;
    return ret;
}

ALStackNode *createALStackNode(int data) {
    ALStackNode *ret = (ALStackNode *)calloc(sizeof(ALStackNode), 1);
    if (!ret) return NULL;
    ret->data_ = data;
    return ret;
}

bool    clearALStack(ALStackBucket *sBucket) {
    if (sBucket->currentElementCount_ > 0) free(sBucket->sl_);
    sBucket->sl_ = NULL;
    sBucket->currentElementCount_ = 0;
    sBucket->sl_ = (ALStackNode *)calloc(sizeof(ALStackNode), sBucket->maxSize_);
    if (sBucket->sl_) return false;
    return true;
}

bool    deleteALStack(ALStackBucket *sBucket) {
    if (sBucket->currentElementCount_ > 0) free(sBucket->sl_);
    free(sBucket);
    sBucket = NULL;
    return true;
}

int     peakStackTopData(ALStackBucket *sBucket) {
    return sBucket->currentElementCount_ == 0 ? 0 : sBucket->sl_[sBucket->currentElementCount_ - 1].data_; 
};

ALStackNode* peakStackTopNode(ALStackBucket *sBucket) {
    return sBucket->currentElementCount_ == 0 ? NULL: &(sBucket->sl_[sBucket->currentElementCount_ - 1]);
};

int     popStackTopData(ALStackBucket *sBucket) {
    ALStackNode n;
    
    if (sBucket->currentElementCount_ == 0) return 0;
    n.data_ = sBucket->sl_[sBucket->currentElementCount_ - 1].data_;
    sBucket->sl_[sBucket->currentElementCount_ - 1].data_ = 0;
    sBucket->currentElementCount_--;
    return n.data_;
};

ALStackNode* popStackTopNode(ALStackBucket *sBucket) {
    if (sBucket->currentElementCount_ == 0) return 0;
    ALStackNode *nptr = createALStackNode(sBucket->sl_[sBucket->currentElementCount_ - 1].data_);
    if (!nptr) return NULL;
    sBucket->sl_[sBucket->currentElementCount_ - 1].data_ = 0;
    sBucket->currentElementCount_--;
    return nptr;
};

bool    pushALStackData(ALStackBucket *sBucket, int data) {
    if (sBucket->currentElementCount_ == sBucket->maxSize_) {
        if (resizeALStack(sBucket, sBucket->currentElementCount_ * 2) == false)
            return false;
    }
    sBucket->sl_[sBucket->currentElementCount_].data_ = data;
    sBucket->currentElementCount_++;
    return true;
};

bool    pushALStackElement(ALStackBucket *sBucket, ALStackNode *element) {
    if (!element) return false;
    if (sBucket->currentElementCount_ == sBucket->maxSize_) {
        if (resizeALStack(sBucket, sBucket->currentElementCount_ * 2) == false)
            return false;
    }
    sBucket->sl_[sBucket->currentElementCount_].data_ = element->data_;
    sBucket->currentElementCount_++;
    return true;
};

size_t  getALStackSize(ALStackBucket *sBucket) {
    return sBucket->currentElementCount_;
};

bool    resizeALStack(ALStackBucket *sBucket, size_t wanted_size) {
    ALStackNode *buf = (ALStackNode *)calloc(sizeof(ALStackNode), wanted_size);
    if (!buf) return false;
    for (size_t i = 0; i < sBucket->currentElementCount_; i++) {
        buf[i].data_ = sBucket->sl_[i].data_;
    }
    free(sBucket->sl_);
    sBucket->sl_ = buf;
    sBucket->maxSize_ = wanted_size;
    return true;
};

void    displayALStack(ALStackBucket *sBucket) {
    if (sBucket->currentElementCount_ == 0) {
        printf("current_size : %zu\ncurrent_top_value : None\nmax_size : %zu\n", 
            sBucket->currentElementCount_,
            sBucket->maxSize_);
        return ;
    }
    printf("current_size : %zu\ncurrent_top_value : %d\nmax_size : %zu\n", 
        sBucket->currentElementCount_,
        peakStackTopData(sBucket),
        sBucket->maxSize_);
};
