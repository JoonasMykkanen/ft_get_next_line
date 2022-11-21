#include <stdio.h>
#include "get_next_line.h"


int	main()
{
	int		fd;
	char	*file;
	char 	*line;

	file = "files/file.txt";
	fd = open(file, O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	free(line);
	fflush(stdout);
	while (line)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
		fflush(stdout);
	}
	close(fd);
	return (0);
}