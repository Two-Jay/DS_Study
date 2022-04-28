#include "../includes/pathFinder.h"

int printSolution(int **mapMatrixt, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mapMatrixt[i][j] == MAPTILE_PASSED) printf("🟩");
            if (mapMatrixt[i][j] == MAPTILE_SPACE) printf("⬜");
            if (mapMatrixt[i][j] == MAPTILE_WALL) printf("🟫");
            if (j == width - 1)
                printf("\n");
        }
	}
    printf("map height : %d, map width : %d\n", height, width);
    return CLEARY_DONE;
}

// 해당 함수에서는 data 오브젝트를 받아 모든 자원을 활용할 수 있도록 했습니다.
// 스펙은 우리가 하면서 편한대로 바꾸면 됩니다.
// 활용할 스텍의 구조와 들어갈 정보 등은 정하지 않았습니다.
// 우리는 여기서의 계산 결과를 토대로 data->mapMatrix의 정보를 변환한 후에
// 아래의 프린트 함수로 찾은 길에 대한 정보를 띄워보려고 합니다.

int **copyMapMatrix(int **mapMatrix, int h, int w) {
    int **ret = (int **)malloc(sizeof(int *) * (h + 1));
    if (!ret) return NULL;
    ret[h] = NULL;
    for (int i = 0; i < h; i++){
        ret[i] = (int *)calloc(sizeof(int *), (w + 1));
        if (!ret[i]) return freeMapMatrix(ret);
        ret[i][w] = '\0';
        for (int j = 0; j < w; j++) {
            ret[i][j] = mapMatrix[i][j];
        }
    }
    return ret;
}

bool isArrive(int x, int y) {
    return ((x == data->mapHeight) && (y == data->mapWidth));
}

// data->mapMatrix 이중배열은 [세로길이][가로길이]이다.

// 0,0 > x, y
int findPath(Data *data) {
    int **map = copyMapMatrix(data->mapMatrix, data->mapHeight, data->mapWidth);
    freeMapMatrix(map);
    return printSolution(data->mapMatrix, data->mapHeight, data->mapWidth);
};

