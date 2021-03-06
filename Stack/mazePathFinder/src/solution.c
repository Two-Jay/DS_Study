#include "../includes/pathFinder.h"

int printSolution(int **mapMatrixt, int height, int width) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (mapMatrixt[i][j] == MAPTILE_PASSED) printf("๐ฉ");
            if (mapMatrixt[i][j] == MAPTILE_SPACE) printf("โฌ");
            if (mapMatrixt[i][j] == MAPTILE_WALL) printf("๐ซ");
            if (j == width - 1)
                printf("\n");
        }
	}
    printf("map height : %d, map width : %d\n", height, width);
    return CLEARY_DONE;
}

// ํ์ฑํ data->mapMatrix์ ๋๊ฐ์ int** ๋ฐฐ์ด์ ํ๋ ๋ ๋ณต์ฌํด์ค๋๋ค.
// ์ด int ** ๋ฐฐ์ด์์ ์์๋ก visited์ฒดํฌ๋ฅผ ํ๋ฉด์ ๊ฐ๋ฅํ ๊ฒฝ๋ก๋ฅผ ํ์ํด ์ค ๊ฒ์๋๋ค.
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

// player๋ฅผ ์์ฑํ๋ ํจ์์๋๋ค.
// ๋์ ํ ๋น์ผ๋ก ์์ฑํ์ฌ ๋๊ฒจ์ฃผ๊ณ , ๋ค์์ผ๋ก ๋๊ฐ direction์ ์ค์ ํด์ค๋๋ค.
MapPosition *initPlayer(int **map, MazeStepStack* pStack) {
    MapPosition *ret = (MapPosition *)calloc(sizeof(MapPosition), 1);
    if (!ret) return NULL;
    // ์ถ๋ฐ์ ์ 0,0 ์๋๋ค.
    ret->x = 0;
    ret->y = 0;
    // player๊ฐ ์งํํ  ๋ฐฉํฅ์ ์ค์ ํฉ๋๋ค.
    // ํด๋น ๋ฐฉํฅ์ ๊ฐ์ ๊ธฐ์ค์ผ๋ก player๋ ์ ์งํ๊ณ , ๋ฐฉํฅ์ ๋ฐ๊ฟ๋์ ์ด ๊ฐ์ ํน์ ๊ฐ์ ํ ๋นํฉ๋๋ค.
    // 0,0 ์ ๋จ์ชฝ์ ์ฒดํฌํด์ ์งํ๊ฐ๋ฅํ๋ฉด ๋จ์ชฝ์ผ๋ก, ์๋๋ผ๋ฉด ๋์ชฝ์ผ๋ก ์ค์ ํฉ๋๋ค.
    // ๋น์ฐํ 0,0์ด ์ถ๋ฐ์ ์ด๋ ์์ชฝ๊ณผ ๋ถ์ชฝ์ผ๋ก ์ค์ ํ๋ฉด ์๋๊ฒ ์ฃ ?
    ret->direction = map[1][0] == MAPTILE_SPACE ? SOUTH : EAST;
    // ๊ฒฝ๋ก๋ฅผ ํ์ํ๋ ๋งต์์ ํ์ฌ ์ถ๋ฐ์ ์ ๊ฐ์ ๋ฐ๊พธ๊ณ 
    map[0][0] = MAPTILE_PASSED;
    // ์ถ๋ฐ์  0,0์ ์คํ์ ์ถ๊ฐํฉ๋๋ค.
    MazeStepNode *start_position = createMazeStepNode(0, 0);
    pushMazeStack(pStack, *start_position);
    free(start_position);
    return ret;
}

// ๋์ฐฉ์ง์ ์ธ์ง ์ฒดํฌํฉ๋๋ค.
// 0 based index ๊ธฐ์ค์ด๊ธฐ์ ๊ฐ ๊ฐ์ -1 ์ฉ ํด์ค๋๋ค.
bool isArrive(int y, int x, Data *data) {
    return ((y == data->mapHeight - 1) && (x == data->mapWidth - 1));
}

// player์ ํ์ฌ direction๊ธฐ์ค์ผ๋ก ํ ์นธ ์์ด move๊ฐ๋ฅํ์ง ์ฒดํฌํ๋ ํจ์์๋๋ค.
bool isPossiblePass(MapPosition *player, int *drct_set, int** map, Data *data) {
    // ์ ์งํ๋ค๊ณ  ๊ฐ์ ํ ๊ฐ์์ ์์น๊ฐ์ ์์ฑํฉ๋๋ค.
    int target_x = player->x + drct_set[1];
    int target_y = player->y + drct_set[0];
    // ๊ทธ ์์น๊ฐ์ด ๋งต ๋ฐ์ ๋ฒ์ด๋ฌ๋์ง ๋จผ์  ์ฒดํฌํฉ๋๋ค.
    if (target_x < 0 || target_y < 0
        || target_y >= data->mapHeight || target_x >= data->mapWidth) return false;
    // ๋ง์ผ ๋งต์์์ ๊ฐ์์ ์์น๊ฐ์ด ๋น ๊ณต๊ฐ์ด๋ผ๋ฉด (move ๊ฐ๋ฅํ๋ค๋ฉด) true๋ฅผ ๋ฆฌํดํ๊ณ  ์๋๋ผ๋ฉด false๋ฅผ ๋ฆฌํดํฉ๋๋ค.
    // ์ด๋ฏธ ๋ค๋ฆฐ ๊ณณ(MAPTILE_PASSED)์ ๋ค์ ๋ฐฉ๋ฌธํ์ง ์์ต๋๋ค.
    return (map[target_y][target_x] == MAPTILE_SPACE) ? true : false;
}

// player๊ฐ ์ด๋ํ๋ ํจ์์๋๋ค.
// ํ์ฌ ์ค์ ๋ direction์ ํ ์นธ ์์ผ๋ก ์ด๋ํ๋ ํจ์์๋๋ค.
bool move(MapPosition *player, int *drct_set, int** map, MazeStepStack *pStack) {
    // ๊ตณ์ด ์ฌ๊ธฐ์ ์ด ์์นธ์ด ์ด๋๋ถ๊ฐ์ธ์ง ์์ธ์ฒ๋ฆฌํ์ง ์์ต๋๋ค. ์๋์ ๋ฐ๋ณต๋ฌธ์์ ์ฒดํฌํด์ฃผ๋๊น์.
    // ํ์ฌ ์์น๊ฐ์ ๋ณ๊ฒฝํ๋ฉฐ ์ ์งํฉ๋๋ค. ์ drct_set[1] ๊ณผ [0]์ ๋ํ๋์ง๋ ํจ์ ์คํ๋ถ๋ถ์ ํ๋ผ๋ฏธํฐ๋ฅผ ์ฐธ๊ณ ํ์ธ์.
    player->x += drct_set[1];
    player->y += drct_set[0];
    // ๋์ฐฉํ ์ง์ ์ ํ์ผ๊ฐ์ ๋ฐ๊พธ์ด์ค๋๋ค.
    map[player->y][player->x] = MAPTILE_PASSED;
    // ์คํ์ ๋์ฐฉํ ์ง์ ์ ์์น๊ฐ์ ๋ฃ์ ๋ธ๋๋ฅผ ๋์ ํ ๋นํ๊ณ 
    // ์คํ์ ๋ฃ์ด์ฃผ๊ณ  ํ๋ฆฌํฉ๋๋ค.
    MazeStepNode *nptr = createMazeStepNode(player->y, player->x);
    pushMazeStack(pStack, *nptr);
    free(nptr);
    return true;
}

// ํ์ฌ ์์น๊ฐ ๋ง๋ค๋ฅธ ๊ธธ์ธ์ง ์ฒดํฌ
// ๋ ์ข์ ๋ฐฉ๋ฒ์ด ์์ํ์ง๋ง ์ผ๋จ์ ์คํ์ ๋ฝ์ผ๋ฉฐ ์ผ๋ฆญํฐ๊ฐ ๊ฑธ์ด์จ ๋ฐฉํฅ๋ ๋ฐ๋๊ธฐ์ ๊ทธ๋ฅ ๋ฌด์ํ๊ฒ ์ธก์ ํด์ค๋๋ค.
bool isDeadEnd(MapPosition *player, int** map, Data *data) {
    if (isPossiblePass(player, DIRECTION[WEST], map, data) == false
        && isPossiblePass(player, DIRECTION[EAST], map, data) == false
        && isPossiblePass(player, DIRECTION[SOUTH], map, data) == false
        && isPossiblePass(player, DIRECTION[NORTH], map, data) == false)
        return true;
    return false;
}

bool revertMove(MapPosition *player, int** map, Data *data, MazeStepStack *pStack) {
    // ์คํ์ ์๋ ์คํ์ pop ํ๋ฉด์ ์ด๋๊ฐ๋ฅํ ์ง์ ๊น์ง ๋ค์ ๋๋์๊ฐ๋ ํจ์์๋๋ค.
    // '์ด๋๊ฐ๋ฅํ ์ง์ '์ด๋ ์ฃผ์์ ๊ฐ ์ ์๋ ๊ธธ์ด ์๋ ๊ณณ (MAPTILE_SPACE)์ ๋งํฉ๋๋ค.
    // ๋๋์์ค๋ ์ค์๋ ์ค๋ฉด์ ๋ณ๊ฒฝํด๋ MAPTILE_PASSED ๋ฅผ ๋ฐ๋ก ๋ณ๊ฒฝํ์ง ์์ต๋๋ค.
    // ์ ๋ต์ด ๋์ถ๋๋ฉด ๋์ค์ ์คํ์์ ๋นผ์ ๊ฒ์ฌํ๋ฉด ๋๋๊น์!
    MazeStepNode *nptr;
    // ์คํ์ด ๋น ๋๊น์ง ๋ฐ๋ณต๋ฌธ์ ๋์์ค๋๋ค. (์คํ์ด ๋น ๊ฒ์ ํ์ถ ์กฐ๊ฑด)
    while (isMazeStepStackEmpty(pStack) == false) {
        // ๋ง๋ค๋ฅธ ๊ธธ์ด ์๋ ๊ฒฝ์ฐ, ์ฆ ์งํ๊ฐ๋ฅํ ๊ฒฝ๋ก๊ฐ ์๋ ๊ฒฝ์ฐ, ์ ๋๋ก ์ฐพ์์๊ธฐ์ ๋ฐ๋ณต๋ฌธ์ ํ์ถํฉ๋๋ค.
        if (isDeadEnd(player, map, data) == false) break ;
        // ํ๋์ฉ ์คํ์์ ๋ธ๋๋ฅผ ๋ฝ์ผ๋ฉฐ, ์ด์  ๊ฒฝ๋ก๋ฅผ ๋๋์ ์ต๋๋ค.
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
    // ๋ง์ง๋ง์ ์คํ ์ฌ์ด์ฆ ์ฒดํฌํด์ ๋ฆฌํด
    // ๋ง์ฝ ์ค๊ฐ์ ์คํ์ด ํํ ๋น๋ค ? ์๋์๋ฆฌ๋ก ๋๋์ ์จ ๊ฒ์ด๋ ์คํจํ ๋งต์ผ๋ก ํ์  == false
    // ๊ทธ๋ ์ง ์์ผ๋ฉด ๋ถ๊ธฐ์ ์ผ๋ก ๋๋์์ค๊ธฐ ์ฑ๊ณต == true 
};

// player์ ํ์ฌ ๋ฐฉํฅ์ ๋ฐ๋ก ์์ด ๋งํ์๊ณ  (move๊ฐ ๋ถ๊ฐ๋ฅํ๊ณ ) && ๋ง๋ค๋ฅธ ๊ธธ์ด ์๋ ๊ฒฝ์ฐ์ ์คํ๋๋ ํจ์์๋๋ค.
// ์ข์ฐ ๋ฐฉํฅ์ด ์งํ๊ฐ๋ฅํ์ง ์ฒดํฌํ ์ดํ, player์ ๋ฐฉํฅ์ ๋ณ๊ฒฝํด์ค๋๋ค.
// ๋ง์ฝ ๋ ๋ค ์งํ์ด ๊ฐ๋ฅํ๋ค๋ฉด, ์ค๋ฅธ์ชฝ์ ๋จผ์  ์งํํด์ค๋๋ค. ์ผ์ชฝ๋ง ๊ฐ๋ฅํ  ๊ฒฝ์ฐ ์ผ์ชฝ์ผ๋ก ๊ฐ์ค๋๋ค. (์ค๋ฅธ์์ ๋ฒ์น ์ ์ฉ)
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
    // ์ถ๋ฐ์ ๊ณผ ๋์ฐฉ์ ์ ๋ฒฝ์ด ์๋ค๋ฉด ์๋ฌ๋ก ๋ฆฌํดํฉ๋๋ค.
    if (data->mapMatrix[0][0] == MAPTILE_WALL
        || data->mapMatrix[data->mapHeight - 1][data->mapWidth - 1] == MAPTILE_WALL)
        return ERROR;
    // ํ์ ๋ชฉ์ ์ผ๋ก ๋ณต์ฌํ  int **๋งต, ํ์์ ์ฃผ์ฒด์ธ player, ํ์ํ ์คํ์ ์ ์ฅํ๊ธฐ ์ํ ์คํ์ ๋์ ํ ๋นํฉ๋๋ค.
    // ๋์ ํ ๋น์ ์คํจํ  ๊ฒฝ์ฐ, ๋ชจ๋ ํ๋ฆฌํด์ฃผ๊ณ  ์๋ฌ๋ฅผ ๋ฆฌํดํฉ๋๋ค.
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

    // ์ถ๋ฐ์ ์์ ํ์์ ์์ํฉ๋๋ค.
    // ์คํ์ด ๋น์ด์๋ ๊ฒฝ์ฐ ๋ค์ ์ถ๋ฐ์ ์ผ๋ก ๋๋์์จ ๊ฒฝ์ฐ์ด๊ธฐ์ ๋ฐ๋ณต๋ฌธ์ ์ข๋ฃํฉ๋๋ค.
    while (isMazeStepStackEmpty(pStack) == false) {
        // ๋์ฐฉํ์์ผ๋ฉด ๋ฐ๋ณต๋ฌธ์ ํ์ถํฉ๋๋ค.
        if (isArrive(player->y, player->x, data)) break ;
        // player์ ํ์ฌ direction์ผ๋ก ๊ณ์ ์์ผ๋ก ๊ฐ ์ ์๋ ์ํ๋ผ๋ฉด
        else if (isPossiblePass(player, DIRECTION[player->direction], map, data) == true) {
            // player์ ํ์ฌ direction์ผ๋ก 1์นธ ์ ์งํฉ๋๋ค.
            move(player, DIRECTION[player->direction], map, pStack);
        }
        // ํ์ฌ ์์น๊ฐ ๋ง๋ค๋ฅธ ๊ธธ์ด๋ผ๋ฉด
        else if (isDeadEnd(player, map, data) == true) {
            // ๊ฐ ์ ์๋ ๋ค๋ฅธ ๊ธธ์ด ๋์ฌ ๋๊น์ง ์คํ์์ ํ๋์ฉ ๋ฝ์ผ๋ฉฐ ๋๋์๊ฐ๋๋ค.
            revertMove(player, map, data, pStack);
        } else {
            // ์ด ๊ฒฝ์ฐ ๋ง๋ค๋ฅธ ๊ธธ๋ ์๋๊ณ , player์ ํ์ฌ direction์ผ๋ก ๊ฐ ์ ์๋ ์ํฉ,
            // ์ฆ ์ผ์ชฝ ํน์ ์ค๋ฅธ์ชฝ์ ๊ฐ ์ ์๋ ๊ธธ์ด ์๋ ์ํฉ์๋๋ค.
            // ๋ ์ค ์ด๋ ๊ธธ๋ก ๊ฐ ์ ์๋์ง ์ฒดํฌํ ๋ค์ ๋ฐฉํฅ์ ์ค์ ํฉ๋๋ค.
            turnDirection(player, map, data);
        }
    };

    // ์ฐพ์๋ธ ๊ฒฝ๋ก๋ฅผ data->mapMatrix์ ์ฒดํฌํ ๋ค์ ํ์ค์ถ๋ ฅ์ผ๋ก ๋ณด์ฌ์ค๋๋ค.
    showSolutionPath(data, pStack);
    // ์ด ํจ์์ ์ค์ฝํ ๋ด์์ ๋์ ํ ๋นํ๋ ๋ชจ๋  ๋ฉ๋ชจ๋ฆฌ๋ฅผ ํค์ ํฉ๋๋ค.
    free(player);
    deleteMazeStepStack(pStack);
    freeMapMatrix(map);
    return CLEARY_DONE;
};



