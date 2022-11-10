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

typedef struct s_str
{
	char	*ptr;
	size_t	len;
	size_t	i;
}

char	*read_line()
{
	
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