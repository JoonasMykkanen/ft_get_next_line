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

size_t	ft_strlen(char const *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static	char	*wrte(char *str, char const *s1, char const *s2)
{
	int	i;
	int	l;

	i = 0;
	l = 0;
	while (s1[i] != '\0')
	{
		str[l] = s1[i];
		i++;
		l++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str[l] = s2[i];
		i++;
		l++;
	}
	str[l] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*str;

	if (s1 && s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		str = (char *)malloc(sizeof(char) * ((l1 + l2) + 1));
		if (str == NULL)
			return (NULL);
		str = wrte(str, s1, s2);
		return (str);
	}
	return (NULL);
}

char	*build_str()
{

}

// char	*check_nl(char *storage, char *buf, int ret, int count)
// {
// 	int		i;
// 	char 	*temp;

// 	i = 0;
// 	temp = malloc(sizeof(char) * ret + 1);
// 	while ()
// }

char	*read_line(char *line, int fd, int ret)
{
	char	*buf[BUFFER_SIZE];
	char	*storage;
	int		count;

	ret = read(fd, buf, BUFFER_SIZE);
	storage = malloc(sizeof(char) * (ret + 1));
	strlcpy(storage, buf, 4);
	printf("%s", storage);
	while (ret)
	{
		// storage = check_nl(storage, buf, ret, count);
		// write(1, buf, ret);
		ret = read(fd, buf, BUFFER_SIZE);
		count++;
	}
	return (storage);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	int			ret;
	char		*line;

	line = read_line(line, fd, ret);
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
