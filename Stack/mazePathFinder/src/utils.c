#include "../includes/pathFinder.h"
#include <string.h>
#define BUFFER_SIZE 10
#define OPEN_MAX 256

#define GNL_ERROR -1
#define GNL_EOF 0
#define GNL_NORMAL_DONE 1

static char	*ft_free_queue(int fd, char **queue) {
	free(queue[fd]);
	queue[fd] = 0;
	return (NULL);
}

static char	*ft_addback_str(char *s1, char *s2) {
	if (!s1 && !s2) return (NULL);
	if (!s1 || !s2) return (!s1) ? strdup(s2) : strdup(s1);
	size_t s1_l = strlen(s1);
	size_t s2_l = strlen(s2);
	char	*ret = malloc(sizeof(char) * (s1_l + s2_l + 1));
	if (!ret) return (NULL);
	memcpy(ret, s1, s1_l);
	free(s1);
	memcpy((ret + s1_l), s2, s2_l);
	ret[s1_l + s2_l] = '\0';
	return (ret);
}

static int	ft_dequeue_text(int fd, char *lon, char **queue, char **line) {
	char	*tmp_ptr = 0;

	// 개행이 있을때 "ㅇㄴㅁㅇㄴㅁㅇㅁㄴ\nㅇㄴㅁㅇㅁㄴ"
	if (*lon == '\n') {
		*lon = '\0';
		tmp_ptr = queue[fd];
		*line = strdup(queue[fd]);
		queue[fd] = strdup(lon + 1);
		free(tmp_ptr);
		tmp_ptr = 0;
		return GNL_NORMAL_DONE;
	}
	// 개행이 없을때 "ㅇㄴㅁㅇㄴㅁㅇㅁㄴ\0"
	else if (*lon == '\0') {
		*line = strdup(queue[fd]);
		ft_free_queue(fd, queue);
		return GNL_EOF;
	}
	else
		return GNL_ERROR;
}

static char	*ft_enqueue_text(int fd, char **queue) {
	int		read_byte = BUFFER_SIZE;
	char	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	char	*n_ptr = 0;

	if (!buf) return (NULL);
	while (!n_ptr && read_byte == BUFFER_SIZE) {
		if ((read_byte = read(fd, buf, BUFFER_SIZE)) <= 0) break ;
		buf[read_byte] = '\0';
		queue[fd] = ft_addback_str(queue[fd], buf);
		n_ptr = strchr(queue[fd], '\n');
	}
	free(buf);
	if (read_byte < 0) ft_free_queue(fd, queue);
	return n_ptr ? n_ptr : (queue[fd] + strlen(queue[fd]));
}

int	ft_strgnl(int fd, char **line) {
	if (fd < 0 || BUFFER_SIZE <= 0 || !line) return (GNL_ERROR);
	static char	*queue[OPEN_MAX];
	char		*lon;

	if (!queue[fd]) queue[fd] = strdup("");
	else if ((lon = strchr(queue[fd], '\n'))) return (ft_dequeue_text(fd, lon, queue, line));
	if (!(lon = ft_enqueue_text(fd, queue))) return (GNL_ERROR);
	return (ft_dequeue_text(fd, lon, queue, line));
}