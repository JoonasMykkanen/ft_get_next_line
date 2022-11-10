#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 3
#endif

char	*build_str(char **storage, char *temp, int ret)
{
	int		i;
	char	c;

	i = 0;
	c = temp[i];
	while (c != '\n')
	{
		c = temp[i];
		if (c == '\n')
			write(1, "FOUND\n", 5);
		i++;
	}
}

char	*read_line(int fd)
{
	int		ret;
	char	*temp;
	char	*storage;
	char	buf[BUFFER_SIZE];

	ret = read(fd, buf, BUFFER_SIZE);
	temp = malloc(sizeof(char) * ret);
	storage = malloc(sizeof(char) * ret);
	while (ret)
	{
		memcpy(temp, buf, ret);
		storage = build_str(&storage, temp, ret);
		// write(1, temp, 3);
		ret = read(fd, buf, BUFFER_SIZE);
	}
}

char	*get_next_line(int fd)
{
	static char	*buff;
	char		*line;
	int			ret;


	line = read_line(fd);
	// buff = overflow read bufferista
	return (line);
}

int	main()
{
	int		fd;
	char	*file;
	
	file = "files/file.txt";
	fd = open(file, O_RDONLY);
	get_next_line(fd);
	close(fd);
	return (0);
}