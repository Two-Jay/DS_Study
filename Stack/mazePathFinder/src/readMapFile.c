#include "../includes/pathFinder.h"

static void	fillMaptile(int *arr, char *row, int size) {
	int	ix;
	int	row_l;

	ix = 0;
	row_l = strlen(row);
    for (int i = 0; i < size; i++) {
		if (row[i] == '0')
			*arr++ = MAPTILE_SPACE;
		else if (row[i] == '1')
			*arr++ = MAPTILE_WALL;
		ix++;
	}
}

static int	*mallocMaplstInt(char *row, int width) {
	int	*ret;
	int	ix;
	int	row_l;

	ix = 0;
	row_l = strlen(row);
	ret = (int *)calloc(sizeof(int), (width + 1));
	if (!ret)
		return NULL;
	ret[width] = '\0';
	fillMaptile(ret, row, row_l);
	return (ret);
}

static int	get_max_width_mapdata(Data *data) {
	MapListNode	*lst;
	int			currentWidth;
	int			maxWidth = 0;
    int         j = 0;

	lst = data->maplst->next;
    for (int i = 0; i < data->mapHeight; i++) {
		currentWidth = 0;
        while (lst->mapline[j]) {
            if (lst->mapline[j] != ' ') currentWidth++;
            j++;
        }
		if (maxWidth < currentWidth)
			maxWidth = currentWidth;
		lst = lst->next;
	}
	return (maxWidth);
}

static int	append_mapdata_lst(char *line, MapListNode *lst, int *map_height) {
	MapListNode	*temp;

	if (!(temp = (MapListNode *)malloc(sizeof(MapListNode)))) return ERROR;
	temp->mapline = strdup(line);
    lst->next = temp;
    if (strlen(temp->mapline)) *map_height += 1;
    return (CLEARY_DONE);
}

static int	convertMaplstToInt(Data *data) {
	int				**ret = (int **)malloc(sizeof(int *) * (data->mapHeight + 1));
	MapListNode	*lst = data->maplst->next;

	if (!ret) return ERROR;
	ret[data->mapHeight] = NULL;
    for (int i = 0; i < data->mapHeight; i++) {
		if (!(ret[i] = mallocMaplstInt(lst->mapline, data->mapWidth))) return ERROR;
		lst = lst->next;
	}
	data->mapMatrix = ret;
	return CLEARY_DONE;
}


// 기본적으로 파서는 아래와 같이 동작합니다.
// 0. 맵의 가로세로 길이를 모르기에 라인 하나하나씩 읽어와서 lst로 만들어줍니다.
//      - 이 때 읽어온 맵파일의 내용은 각 라인 별로 maplst->mapline에 동적할당되어 저장됩니다.
// 1. 맵파일 내용을 전부 가져와서 maplst로 저장했다면, 유효한 정보가 있는 기준에 따라 맵의 넓이와 높이를 정합니다.
// 2. 이렇게 가져온 maplst를 맵상의 x, y 인덱스 정보와 해당 인덱스의 벨류로 맵을 다룰 수 있도록 int **mapMatrix로 변환해줍니다. 
int	parseMapfile(const char *mapfile_path, Data *data) {
    // 헤더노드 설정 및 헤더노드 포인터 저장, 매개변수로 온 mapfile_path로 맵파일 열기 
	MapListNode	*lst = (MapListNode *)malloc(sizeof(MapListNode));
	MapListNode	*head;
	int			line_check = 1;
    int         mapfd = open(mapfile_path, O_RDONLY);
	char		*map_line;

    if (mapfd == -1) return ERROR;
    if (!lst) return ERROR;
	head = lst;

	while (line_check > 0) {
        // get_next_line로 맵파일을 연 fd에서 한 줄의 라인을 읽어와서, map_line에 동적할당하여 저장합니다.
		line_check = ft_strgnl(mapfd, &map_line);
        // map_line 저장한 라인을 리스트에 저장하기 위해 노드를 동적할당하여 lst 뒤에 붙여줍니다. 에러시 리턴
		if (append_mapdata_lst(map_line, lst, &(data->mapHeight))) return ERROR;
        // 다음노드로 포인트 조정
        lst = lst->next;
        // get_next_line에서 동적할당으로 받아온 라인 free
        free(map_line);
	}
    // 반복문이 끝났을 시 마지막 라인을 받아옵니다. 위의 연산을 마지막으로 한 번 더 해줍니다.
    if (append_mapdata_lst(map_line, lst, &(data->mapHeight))) return ERROR;
	// 저장한 헤더의 정보 set, data->mapWidth에 맵의 넓이를 구해서 저장합니다.
    data->maplst = head;
	data->mapWidth = get_max_width_mapdata(data);
    // data->maplst를 int ** 기반의 mapMatrix로 변환합니다.
    convertMaplstToInt(data);
	return CLEARY_DONE;
}
