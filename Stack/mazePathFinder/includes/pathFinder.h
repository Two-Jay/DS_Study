#ifndef _MAP_DEF_
#define _MAP_DEF_

#define WIDTH 8
#define HEIGHT 8

#define NUM_DIRECTIONS 4

#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mazeStack.h"

// offset: x, y
static int DIRECTION_OFFSETS[NUM_DIRECTIONS][2] = {
	{0, -1},		// �������� �̵�.
	{1, 0},			// ���������� �̵�.
	{0, 1},			// �Ʒ������� �̵�.
	{-1, 0}			// �������� �̵�.
};

enum PosStatus { NOT_VISIT = 0, WALL = 1 , VISIT = 2  };

typedef struct MapPositionType
{
	int x;				// ���� ��ġ x��ǥ.
	int y;				// ���� ��ġ y��ǥ.
	int direction;		// ���� ��ġ�� �̵� ����.
} MapPosition;

typedef struct maplst {
	char *mapline;
	struct maplst *next;
}	MapListNode;

typedef struct Data {
    int **mapMatrix;
	MapListNode *maplst;
    int mapWidth;
    int mapHeight;
}   Data;

int	parseMapfile(const char *mapfile_path, Data *data);
int	ft_strgnl(int fd, char **line);
int freeData(Data *data);
int freeMapMatrix(int **map);
int findPath(Data *data);

#endif // _MAP_DEF_

#ifndef _MAPFILE_ALIAS_
#define _MAPFILE_ALIAS_

#define ERROR 1
#define CLEARY_DONE 0

#define MAPTILE_PASSED 2
#define MAPTILE_WALL 1
#define MAPTILE_SPACE 0

#define ERROR_END_ARGC 2
#define ERROR_END_MAIN 4

#endif // _MAPFILE_ALIAS_

#ifndef _MAPPARSER_TEST_FUNCTION_
#define _MAPPARSER_TEST_FUNCTION_

int test_printMaplst(MapListNode *maplst_header, int height, int width);
int test_printMapMatrix(int **mapMatrixt, int height, int width);

#endif // _MAPPARSER_TEST_FUNCTION_
