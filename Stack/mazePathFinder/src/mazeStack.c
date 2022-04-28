#include "../includes/pathFinder.h"

MazeStepStack *createMazeStepStack(void) {
    MazeStepStack *ret = (MazeStepStack *)calloc(sizeof(MazeStepStack), 1);
    if (!ret) return NULL;
    return ret;
}

MazeStepNode *createMazeStepNode(int y, int x) {
    MazeStepNode *ret = (MazeStepNode *)calloc(sizeof(MazeStepNode), 1);
    if (!ret) return NULL;
    ret->x = x;
    ret->y = y;
    return ret;
}

void pushMazeStack(MazeStepStack *pStack, MazeStepNode element) {
    MazeStepNode *pNewNode = createMazeStepNode(element.y, element.x);
    if (isMazeStepStackEmpty(pStack) == true) {
        pStack->PrevSteps = pNewNode;
        pStack->currentElementCount++;
    } else {
        pNewNode->pLink = pStack->PrevSteps;
        pStack->PrevSteps = pNewNode;
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

int getSizeMazeStack(MazeStepStack *pStack) {
    return pStack->currentElementCount;
}