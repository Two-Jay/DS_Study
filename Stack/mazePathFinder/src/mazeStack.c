#include "../includes/pathFinder.h"

MazeStepStack *createMazeStepStack(void) {
    MazeStepStack *ret = (MazeStepStack *)calloc(sizeof(MazeStepStack), 1);
    if (!ret) return NULL;
    ret->PrevSteps = (MazeStepNode *)calloc(sizeof(MazeStepNode), 1);
    if (!ret->PrevSteps) {
        free(ret);
        return NULL;
    }
    return ret;
}

MazeStepNode *createMazeStepNode(int x, int y, int direction) {
    MazeStepNode *ret = (MazeStepNode *)calloc(sizeof(MazeStepNode), 1);
    if (!ret) return NULL;
    ret->x = x;
    ret->y = y;
    ret->direction = direction;
    return ret;
}

void pushMazeStack(MazeStepStack *pStack, MazeStepNode *element) {
    if (isMazeStepStackEmpty(pStack) == true) {
        pStack->PrevSteps = element;
        pStack->currentElementCount++;
    } else {
        element->pLink = pStack->PrevSteps;
        pStack->PrevSteps = element;
        pStack->currentElementCount++;
    }
}

MazeStepNode *popMazeStack(MazeStepStack *pStack) {
    MazeStepNode *ret = pStack->PrevSteps;
    if (isMazeStepStackEmpty(pStack) == true) return NULL;
    pStack->PrevSteps = ret->pLink;
    pStack->currentElementCount--;
    ret->pLink = NULL;
    return ret;
}

void deleteMazeStepStack(MazeStepStack *pStack) {
    size_t limit = pStack->currentElementCount;
    for (size_t i = 0; i < limit; i++) {
        MazeStepNode *nptr = popMazeStack(pStack);
        free(nptr);
    }
    free(pStack);
}

MazeStepNode *peekMazeStepStack(MazeStepStack *pStack) {
    return pStack->PrevSteps;
}

bool isMazeStepStackEmpty(MazeStepStack *pStack) {
    return pStack->currentElementCount == 0;
}