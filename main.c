#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int				main(int argc, char **argv)
{
	//int			i;
	int			fd, fd2;
	char		*line;

	if (argc == 3)
	{
	//	i = 0;
		fd = open(argv[1], O_RDONLY);
		fd2 = open(argv[2], O_RDONLY);
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
	}
	return (0);
}
