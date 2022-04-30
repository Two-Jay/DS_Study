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

// 파싱한 data->mapMatrix와 똑같은 int** 배열을 하나 더 복사해줍니다.
// 이 int ** 배열에서 임시로 visited체크를 하면서 가능한 경로를 탐색해 줄 것입니다.
int **copyMapMatrix(int **mapMatrix, int h, int w) {
    int **ret = (int **)malloc(sizeof(int *) * (h + 1));
    if (!ret) return NULL;
    ret[h] = NULL;
    for (int i = 0; i < h; i++){
        ret[i] = (int *)calloc(sizeof(int *), (w + 1));
        if (!ret[i]) {
            freeMapMatrix(ret);
            return NULL;
        }
        ret[i][w] = '\0';
        for (int j = 0; j < w; j++) {
            ret[i][j] = mapMatrix[i][j];
        }
    }
    return ret;
}

// player를 생성하는 함수입니다.
// 동적할당으로 생성하여 넘겨주고, 다음으로 나갈 direction을 설정해줍니다.
MapPosition *initPlayer(int **map, MazeStepStack* pStack) {
    MapPosition *ret = (MapPosition *)calloc(sizeof(MapPosition), 1);
    if (!ret) return NULL;
    // 출발점은 0,0 입니다.
    ret->x = 0;
    ret->y = 0;
    // player가 진행할 방향을 설정합니다.
    // 해당 방향의 값을 기준으로 player는 전진하고, 방향을 바꿀때엔 이 값에 특정값을 할당합니다.
    // 0,0 의 남쪽을 체크해서 진행가능하면 남쪽으로, 아니라면 동쪽으로 설정합니다.
    // 당연히 0,0이 출발점이니 서쪽과 북쪽으로 설정하면 안되겠죠?
    ret->direction = map[1][0] == MAPTILE_SPACE ? SOUTH : EAST;
    // 경로를 탐색하는 맵에서 현재 출발점의 값을 바꾸고
    map[0][0] = MAPTILE_PASSED;
    // 출발점 0,0을 스텍에 추가합니다.
    MazeStepNode *start_position = createMazeStepNode(0, 0);
    pushMazeStack(pStack, *start_position);
    free(start_position);
    return ret;
}

// 도착지점인지 체크합니다.
// 0 based index 기준이기에 각 값에 -1 씩 해줍니다.
bool isArrive(int y, int x, Data *data) {
    return ((y == data->mapHeight - 1) && (x == data->mapWidth - 1));
}

// player의 현재 direction기준으로 한 칸 앞이 move가능한지 체크하는 함수입니다.
bool isPossiblePass(MapPosition *player, int *drct_set, int** map, Data *data) {
    // 전진했다고 가정한 가상의 위치값을 생성합니다.
    int target_x = player->x + drct_set[1];
    int target_y = player->y + drct_set[0];
    // 그 위치값이 맵 밖을 벗어났는지 먼저 체크합니다.
    if (target_x < 0 || target_y < 0
        || target_y >= data->mapHeight || target_x >= data->mapWidth) return false;
    // 만일 맵상에서 가상의 위치값이 빈 공간이라면 (move 가능하다면) true를 리턴하고 아니라면 false를 리턴합니다.
    // 이미 들린 곳(MAPTILE_PASSED)은 다시 방문하지 않습니다.
    return (map[target_y][target_x] == MAPTILE_SPACE) ? true : false;
}

// player가 이동하는 함수입니다.
// 현재 설정된 direction의 한 칸 앞으로 이동하는 함수입니다.
bool move(MapPosition *player, int *drct_set, int** map, MazeStepStack *pStack) {
    // 굳이 여기서 이 앞칸이 이동불가인지 예외처리하지 않습니다. 아래의 반복문에서 체크해주니깐요.
    // 현재 위치값을 변경하며 전진합니다. 왜 drct_set[1] 과 [0]을 더하는지는 함수 실행부분의 파라미터를 참고하세요.
    player->x += drct_set[1];
    player->y += drct_set[0];
    // 도착한 지점의 타일값을 바꾸어줍니다.
    map[player->y][player->x] = MAPTILE_PASSED;
    // 스텍에 도착한 지점의 위치값을 넣은 노드를 동적할당하고
    // 스텍에 넣어주고 프리합니다.
    MazeStepNode *nptr = createMazeStepNode(player->y, player->x);
    pushMazeStack(pStack, *nptr);
    free(nptr);
    return true;
}

// 현재 위치가 막다른 길인지 체크
// 더 좋은 방법이 있을테지만 일단은 스텍을 뽑으며 케릭터가 걸어온 방향도 바뀌기에 그냥 무식하게 측정해줍니다.
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
    // 스텍이 빌 때까지 반복문을 돌아줍니다. (스텍이 빈 것은 탈출 조건)
    while (isMazeStepStackEmpty(pStack) == false) {
        // 막다른 길이 아닐 경우, 즉 진행가능한 경로가 있는 경우, 제대로 찾아왔기에 반복문을 탈출합니다.
        if (isDeadEnd(player, map, data) == false) break ;
        // 하나씩 스텍에서 노드를 뽑으며, 이전 경로를 되돌아 옵니다.
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
    // 마지막에 스텍 사이즈 체크해서 리턴
    // 만약 중간에 스텍이 텅텅 빈다 ? 원래자리로 되돌아 온 것이니 실패한 맵으로 판정 == false
    // 그렇지 않으면 분기점으로 되돌아오기 성공 == true 
};

// player의 현재 방향의 바로 앞이 막혀있고 (move가 불가능하고) && 막다른 길이 아닐 경우에 실행되는 함수입니다.
// 좌우 방향이 진행가능한지 체크한 이후, player의 방향을 변경해줍니다.
// 만약 둘 다 진행이 가능하다면, 오른쪽을 먼저 진행해줍니다. 왼쪽만 가능할 경우 왼쪽으로 가줍니다. (오른손의 법칙 적용)
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
        data->mapMatrix[nptr->y][nptr->x] = MAPTILE_PASSED;
        free(nptr);
    }
    printSolution(data->mapMatrix, data->mapHeight, data->mapWidth);
}

int findPath(Data *data) {
    // 출발점과 도착점에 벽이 있다면 에러로 리턴합니다.
    if (data->mapMatrix[0][0] == MAPTILE_WALL
        || data->mapMatrix[data->mapHeight - 1][data->mapWidth - 1] == MAPTILE_WALL)
        return ERROR;
    // 탐색 목적으로 복사할 int **맵, 탐색의 주체인 player, 탐색한 스텝을 저장하기 위한 스텍을 동적할당합니다.
    // 동적할당에 실패할 경우, 모두 프리해주고 에러를 리턴합니다.
    int **map = copyMapMatrix(data->mapMatrix, data->mapHeight, data->mapWidth);
    if (!map) return ERROR;
    MazeStepStack *pStack = createMazeStepStack();
    if (!pStack) {
        freeMapMatrix(map);
        return ERROR;
    }
    MapPosition *player = initPlayer(map, pStack);
    if (!player) {
        freeMapMatrix(map);
        deleteMazeStepStack(pStack);
        return ERROR;
    }

    // 출발점에서 탐색을 시작합니다.
    // 스텍이 비어있는 경우 다시 출발점으로 되돌아온 경우이기에 반복문을 종료합니다.
    while (isMazeStepStackEmpty(pStack) == false) {
        // 도착하였으면 반복문을 탈출합니다.
        if (isArrive(player->y, player->x, data)) break ;
        // player의 현재 direction으로 계속 앞으로 갈 수 있는 상태라면
        else if (isPossiblePass(player, DIRECTION[player->direction], map, data) == true) {
            // player의 현재 direction으로 1칸 전진합니다.
            move(player, DIRECTION[player->direction], map, pStack);
        }
        // 현재 위치가 막다른 길이라면
        else if (isDeadEnd(player, map, data) == true) {
            // 갈 수 있는 다른 길이 나올 때까지 스텍에서 하나씩 뽑으며 되돌아갑니다.
            revertMove(player, map, data, pStack);
        } else {
            // 이 경우 막다른 길도 아니고, player의 현재 direction으로 갈 수 없는 상황,
            // 즉 왼쪽 혹은 오른쪽에 갈 수 있는 길이 있는 상황입니다.
            // 둘 중 어느 길로 갈 수 있는지 체크한 다음 방향을 설정합니다.
            turnDirection(player, map, data);
        }
    };

    // 찾아낸 경로를 data->mapMatrix에 체크한 다음 표준출력으로 보여줍니다.
    showSolutionPath(data, pStack);
    // 이 함수의 스코프 내에서 동적할당했던 모든 메모리를 헤제합니다.
    free(player);
    deleteMazeStepStack(pStack);
    freeMapMatrix(map);
    return CLEARY_DONE;
};



