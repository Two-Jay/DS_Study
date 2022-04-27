#include "../includes/pathFinder.h"

static int	get_max_width_mapdata(Data *data)
{
	MapListNode	*lst;
	int			currentWidth = 0;
	int			maxWidth = 0;
	int			ix = 0;

	lst = data->maplst->next;
	while (ix < data->mapHeight)
	{
		currentWidth = ft_strlen(lst->mapline);
		if (maxWidth < currentWidth)
			maxWidth = currentWidth;
		lst = lst->next;
		ix++;
	}
	return (maxWidth);
}

static MapListNode	*append_mapdata_lst(char *line, MapListNode *lst)
{
	MapListNode	*temp;

	if (!(temp = (MapListNode *)malloc(sizeof(MapListNode)))) return NULL;
		return (NULL);
	temp->mapline = ft_strdup(line);
	lst->next = temp;
	free(line);
	return (temp);
}

int	parseMapfile(int map_fd, Data *data)
{
	MapListNode	*lst = (MapListNode *)malloc(sizeof(MapListNode));
	MapListNode	*head;
	int			line_check;
	char		*map_line;

    if (!lst) return ERROR;
	head = lst;
	while (line_check > 0)
	{
		if (!(lst = append_mapdata_lst(map_line, lst))) return (ERROR);
		data->mapHeight++;
		line_check = ft_strgnl(map_fd, &map_line);
	}
    if (!(lst = append_mapdata_lst(map_line, lst))) return (ERROR);
	data->mapHeight++;
	data->maplst = head;
	data->mapWidth = get_max_width_mapdata(data);
	return (CLEARY_DONE);
}