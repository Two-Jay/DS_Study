#ifndef _MAP_DEF_
#define _MAP_DEF_

#define WIDTH 8
#define HEIGHT 8

#define NUM_DIRECTIONS 4

#include <unistd.h>
#include <fcntl.h>

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
	struct maplst	*next;
}	MapListNode;

typedef struct d {
    int **mapMatrix;
	MapListNode *maplst;
    int mapWidth;
    int mapHeight;
}   Data;

int	parseMapfile(int map_fd, Data *data);

#define ERROR 1;
#define CLEARY_DONE 0;

#endif