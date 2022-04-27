#include "../includes/pathFinder.h"

void freeMaplist(Data *data) {
    MapListNode *nptr = data->maplst;
    MapListNode *tmp;
    // 헤더노드와, 마지막 EOF처리가 된 노드도 긁어오기에 노드를 2개 더 해제해주어야 함
    int limit = data->mapHeight + 2;
    for (int i = 0; i < limit; i++) {
        tmp = nptr->next;
        if (i != 0) free(nptr->mapline);
        free(nptr);
        nptr = tmp;
    }
};

void freeMapMatrix(Data *data) {
    for (int i = 0; i < data->mapHeight; i++) {
        free(data->mapMatrix[i]);
    }
    free(data->mapMatrix);
};


int freeData(Data *data) {
    freeMaplist(data);
    freeMapMatrix(data);
    free(data);
    data = NULL;
    return CLEARY_DONE;
}