
#ifndef _MAZE_STACK_H_
#define _MAZE_STACK_H_

typedef struct MazeStepNodeType {
	int y;
	int x;
	struct MazeStepNodeType *pLink;
}	MazeStepNode;

typedef struct MazeStepStackType {
	int currentElementCount;
	MazeStepNode *PrevSteps;
}	MazeStepStack;

MazeStepStack *createMazeStepStack(void);
MazeStepNode *createMazeStepNode(int x, int y);
void pushMazeStack(MazeStepStack *pStack, MazeStepNode element);
MazeStepNode *popMazeStack(MazeStepStack *pStack);
void deleteMazeStepStack(MazeStepStack *pStack);
MazeStepNode *peekMazeStepStack(MazeStepStack *pStack);
bool isMazeStepStackEmpty(MazeStepStack *pStack);
int getSizeMazeStack(MazeStepStack *pStack);

#endif // _MAZE_STACK_H_