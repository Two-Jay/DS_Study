
#include "./includes/pathFinder.h"
#include <stdio.h>
#include <string.h>

int error_return(const char *error_msg, int flag) {
    if (flag & ERROR_END_ARGC) printf("Usage './mazePathFinder [mapfile_path]\n");
    else printf("Error : %s\n", error_msg);
    return ERROR;
}

int main(int argc, char **argv) {
    Data *data = NULL;
    if (argc != 2) return error_return(NULL, ERROR_END_ARGC);
    if (!(data = (Data *)calloc(sizeof(data), 1))
        || parseMapfile(argv[1], data)
        || findPath(data)
        || freeData(data))
        return error_return("an error occured", ERROR_END_MAIN);
    system("leaks mazePathFinder > leaks_result; cat leaks_result | grep leaked && rm -rf leaks_result");
    return CLEARY_DONE;
}