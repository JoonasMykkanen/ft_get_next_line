#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>



#ifndef BUFFER_SIZE
# define BUFFER_SIZE 15
#endif



void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	i = 0;
	if (d == NULL && s == NULL)
		return (d);
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

char	*build_str(char *storage, char *temp, int ret, int *trigger)
{
	static int	index = 0;
	char		*str;
	char		c;
	int			i;

	i = 0;
	c = temp[i];
	str = malloc(sizeof(char) * (index + ret + 1));
	ft_memcpy(str, storage, index);
	while (c != '\n' && i < ret)
	{
		c = temp[i];
		str[index + i] = c;
		if (c == '\n')
		{
			str[index + i + 1] = '\0'; 
			*trigger = 1;
			index = 0;
			return (str);
		}
		// printf("current index: %d str: %c\n", (index + i), str[index + i]);
		// write(1, &str[index + i], 1);
		// write(1, "\n", 1);
		i++;
	}
	index += i;
	return (str);
}

char	*read_line(int fd)
{
	int		ret;
	char	*temp;
	int		trigger;
	char	*storage;
	char	buf[BUFFER_SIZE];

	trigger = 0;
	ret = read(fd, buf, BUFFER_SIZE);
	if (!ret)
		return (NULL);
	temp = malloc(sizeof(char) * ret);
	if (!temp)
		return (NULL);
	while (ret)
	{
		ft_memcpy(temp, buf, ret);
		storage = build_str(storage, temp, ret, &trigger);
		if (trigger == 1)
		{
			// handle_overflow();
			break ;
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	// int	xy = strlen(storage);
	// write(1, storage, xy);
	return (storage);
}

char	*get_next_line(int fd)
{
	// static char	*buff;
	char		*line;

	line = read_line(fd);
	// buff = overflow read bufferista
	return (line);
}
