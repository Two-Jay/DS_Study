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


int	parseMapfile(const char *mapfile_path, Data *data) {
	MapListNode	*lst = (MapListNode *)malloc(sizeof(MapListNode));
	MapListNode	*head;
	int			line_check = 1;
    int         mapfd = open(mapfile_path, O_RDONLY);
	char		*map_line;

    if (mapfd == -1) return ERROR;
    if (!lst) return ERROR;
	head = lst;
	while (line_check > 0) {
		line_check = ft_strgnl(mapfd, &map_line);
		if (append_mapdata_lst(map_line, lst, &(data->mapHeight))) return ERROR;
        lst = lst->next;
        free(map_line);
	}
    if (append_mapdata_lst(map_line, lst, &(data->mapHeight))) return ERROR;
	data->maplst = head;
	data->mapWidth = get_max_width_mapdata(data);
    convertMaplstToInt(data);
	return CLEARY_DONE;
}
