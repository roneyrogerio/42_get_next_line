#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int	main(void)
{
	int	fd;
	char	*line;
	int	ret;

	fd = open("test", O_RDONLY);
	while ((ret = get_next_line(fd, &line)))
		printf("return=%d, line=%s\n", ret, line);
	printf("return=%d, line=%s\n", ret, line);
	return (0);
}
