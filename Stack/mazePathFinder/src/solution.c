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

int **copyMapMatrix(int **mapMatrix, int h, int w) {
    int **ret = (int **)malloc(sizeof(int *) * (h + 1));
    if (!ret) return NULL;
    ret[h] = NULL;
    for (int i = 0; i < h; i++){
        ret[i] = (int *)calloc(sizeof(int *), (w + 1));
        if (!ret[i]) return freeMapMatrix(ret), NULL;
        ret[i][w] = '\0';
        for (int j = 0; j < w; j++) {
            ret[i][j] = mapMatrix[i][j];
        }
    }
    return ret;
}


MapPosition *initPlayer(int **map) {
    MapPosition *ret = (MapPosition *)calloc(sizeof(MapPosition), 1);
    if (!ret) return NULL;
    ret->x = 0;
    ret->y = 0;
    ret->direction = map[1][0] == MAPTILE_SPACE ? SOUTH : EAST;
    return ret;
}

bool isArrive(int y, int x, Data *data) {
    return ((y == data->mapHeight - 1) && (x == data->mapWidth - 1));
}

bool isPossiblePass(MapPosition *player, int *drct_set, int** map, Data *data) {
    int target_x = player->x + drct_set[1];
    int target_y = player->y + drct_set[0];
    if (target_x < 0 || target_y < 0
        || target_y >= data->mapHeight || target_x >= data->mapWidth) return false;
    return (map[target_x][target_y] == 0) ? true : false;
}

bool move(MapPosition *player, int *drct_set, int** map, Data *data, MazeStepStack *pStack) {
    if (isPossiblePass(player, drct_set, map, data) == false) return false;
    player->x += drct_set[1];
    player->y += drct_set[0];
    map[player->x][player->y] = MAPTILE_PASSED;
    MazeStepNode *nptr = createMazeStepNode(player->y, player->x);
    pushMazeStack(pStack, *nptr);
    free(nptr);
    return true;
}


bool isDeadEnd(MapPosition *player, int** map, Data *data) {
    if (isPossiblePass(player, DIRECTION[WEST], map, data) == false
        && isPossiblePass(player, DIRECTION[EAST], map, data) == false
        && isPossiblePass(player, DIRECTION[SOUTH], map, data) == false
        && isPossiblePass(player, DIRECTION[NORTH], map, data) == false)
        return true;
    return false;
}

bool revertMove(MapPosition *player, int** map, Data *data, MazeStepStack *pStack) {
    // 스텍에 있는 스텝을 pop 하면서 이동가능한 지점까지 다시 되돌아가는 함수입니다.
    // '이동가능한 지점'이란 주위에 갈 수 있는 길이 있는 곳 (MAPTILE_SPACE)을 말합니다.
    // 되돌아오는 중에는 오면서 변경해둔 MAPTILE_PASSED 를 따로 변경하지 않습니다.
    // 정답이 도출되면 나중에 스텍에서 빼서 검사하면 되니깐요!
    MazeStepNode *nptr;
    printf("size : %d\n", getSizeMazeStack(pStack));
    while (isMazeStepStackEmpty(pStack) == false) {
        if (isDeadEnd(player, map, data) == false) break ;
        nptr = popMazeStack(pStack);
        player->x = nptr->x;
        player->y = nptr->y;
        free(nptr);
    }
    if (isMazeStepStackEmpty(pStack) == true) return false;
    nptr = createMazeStepNode(player->y, player->x);
    pushMazeStack(pStack, *nptr);
    free(nptr);
    return true;
    // false조건도 잘 구해야 할 거 같아요.
    // revertMove를 하는데... 스텍이 비었다?! fail 조건...!
    // 마지막에 스텍 사이즈 체크해서 리턴 : 실패한 맵으로 판정 == false, 되돌아오기 성공 == true 
};

void turnDirection(MapPosition *player, int **map, Data *data) {
    int left = (player->direction - 1 < 0) ? 3 : player->direction - 1;
    int right = (player->direction + 1 > 3) ? 0 : player->direction + 1;
    bool right_boolean = isPossiblePass(player, DIRECTION[right], map, data);
    player->direction = (right_boolean) ? right : left;
}

void showSolutionPath(Data *data, MazeStepStack *pStack) {
    MazeStepNode *nptr;
    while (isMazeStepStackEmpty(pStack) == false) {
        nptr = popMazeStack(pStack);
        data->mapMatrix[nptr->x][nptr->y] = MAPTILE_PASSED;
        free(nptr);
    }
    printSolution(data->mapMatrix, data->mapHeight, data->mapWidth);
}

// data->mapMatrix 이중배열은 [세로길이][가로길이]이다.
// 0,0 > x, y
int findPath(Data *data) {
    if (data->mapMatrix[0][0] == MAPTILE_WALL) return ERROR;
    int **map = copyMapMatrix(data->mapMatrix, data->mapHeight, data->mapWidth);
    if (!map) return ERROR;
    MapPosition *player = initPlayer(map);
        
    if (!player) return freeMapMatrix(map), ERROR;
    MazeStepStack *pStack = createMazeStepStack();
    
    if (!pStack) return freeMapMatrix(map), free(player), ERROR;
    map[0][0] = MAPTILE_PASSED;
    MazeStepNode *start_position = createMazeStepNode(0, 0);
    pushMazeStack(pStack, *start_position);
    free(start_position);
    system("leaks mazePathFinder");

    while (isMazeStepStackEmpty(pStack) == false) {
        if (isArrive(player->y, player->x, data)) break ; // 도착!!!!
        else if (isPossiblePass(player, DIRECTION[player->direction], map, data) == true) {
            move(player, DIRECTION[player->direction], map, data, pStack);
        }
        else if (isDeadEnd(player, map, data) == true) {
            revertMove(player, map, data, pStack);
        } else {
            turnDirection(player, map, data);
        }
    };

    showSolutionPath(data, pStack);
    free(player);
    deleteMazeStepStack(pStack);
    return freeMapMatrix(map);
};



