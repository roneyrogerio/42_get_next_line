#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int	main(void)
{
	int	fd, fd2;
	char	*line;

	fd = open("test", O_RDONLY);
	fd2 = open("test2", O_RDONLY);
	get_next_line(fd, &line);
	printf("%s", line);
	printf("\n");
	get_next_line(fd2, &line);
	printf("%s", line);
	printf("\n");
	get_next_line(fd2, &line);
	printf("%s", line);
	printf("\n");
	get_next_line(fd, &line);
	printf("%s", line);
	printf("\n");
	close(fd);
	close(fd2);
	return (0);
}
