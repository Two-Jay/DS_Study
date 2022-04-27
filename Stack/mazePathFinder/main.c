
#include "./includes/pathFinder.h"
#include <stdio.h>
#include <string.h>

int error_return(const char *error_msg, int flag) {
    if (flag & ERROR_END_ARGC) printf("Usage './mazePathFinder [mapfile_path]\n");
    else printf("Error : %s\n", error_msg);
    return ERROR;
}

int main(int argc, char **argv) {
    // 기본적인 입력과 data 오브젝트 할당 및 널가드 예외처리
    if (argc != 2) {
        printf("Usage './mazePathFinder [mapfile_path]\n");
        return ERROR;
    }
    Data *data = (Data *)calloc(sizeof(data), 1);
    if (!data) return ERROR;
    // 이 함수에서 맵파일을 파싱합니다.
    parseMapfile(argv[1], data);
    // 우리는 이 함수를 작업하면 됩니다. :)
    findPath(data);
    // char * 연결리스트로 파싱해온 데이터 표준출력으로 출력
    test_printMaplst(data->maplst, data->mapHeight, data->mapWidth); 
    // char * 연결리스트로 파싱해온 데이터를 int **으로 변환한 매트릭스를 표준출력으로 출력
    test_printMapMatrix(data->mapMatrix, data->mapHeight, data->mapWidth);    
    // 동적할당 했던 data 오브젝트를 해제해줍니다.
    freeData(data);

    // 중간에 에러가 생길시 진행을 중지하기 위해, 실제로는 아래와 같이 진행합니다. 테스트 함수는 제외했습니다.
    // if (argc != 2) return error_return(NULL, ERROR_END_ARGC);
    // if (!(data = (Data *)calloc(sizeof(data), 1))
    //     || parseMapfile(argv[1], data)
    //     || findPath(data)
    //     || freeData(data))
    //     return error_return("an error occured");
    system("leaks mazePathFinder");
    return CLEARY_DONE;
}