#include "../includes/pathFinder.h"
#include <stdio.h>

void test_printMaplst(MapListNode *maplst_header, int height, int width) {
    printf("data->maplst------------------------\n");
    MapListNode *nptr = maplst_header->next;
    for (int i = 0; i < height; i++) {
        printf("%s\n", nptr->mapline);
		nptr = nptr->next;
	}
    printf("map height : %d, map width : %d\n", height, width);
    printf("data->maplst_test_end---------------\n");
}

void test_printMaplst_converted(int **mapMatrix, int height, int width) {
    printf("data->mapMatrix---------------------\n");
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == width - 1)
                printf("%d\n", mapMatrix[i][j]);
            else                
                printf("%d ", mapMatrix[i][j]);
        }
	}
    printf("map height : %d, map width : %d\n", height, width);
    printf("data->mapMatrix_test_end------------\n");
}
