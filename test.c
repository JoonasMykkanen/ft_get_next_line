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

size_t	ft_strlen(char const *s)
{
	int	i;

	if (s == NULL || !s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

void	*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	ch;
	void			*ptr;
	void			*src;

	i = 0;
	ch = c;
	src = (void *)s;
	while (n > 0)
	{
		if (*((unsigned char *)s + i) == ch)
		{
			ptr = &src[i];
			return (ptr);
		}
		n--;
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[j] != '\0')
	{
		str[i] = s1[j];
		i++;
		j++;
	}
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';	
	return (str);
}

// char	*handle_overflow(unsigned int ret, char *temp, int *index)
// {
// 	unsigned int	len;
// 	char 			*storage;

// 	len = 0;
// 	while (temp[len] != '\n' && len <= ret)
// 	{
// 		*index += 1;
// 		len++;
// 	}
// 	*index += 1;
// 	len++;
// 	len = ret - len;
// 	storage = malloc(sizeof(char) * (len + 1));
// 	if (!storage || len < 1)
// 	{
// 		free(storage);
// 		return (NULL);
// 	}
// 	ft_memcpy(storage, temp + *index, len);
// 	storage[len] = '\0';
// 	return (storage);
// }

void	handle_overflow(char **buff, unsigned int ret, char *temp, int *index)
{
	unsigned int	len;
	char 			*storage;

	len = 0;
	free(*buff);
	while (temp[len] != '\n' && len <= ret)
	{
		*index += 1;
		len++;
	}
	*index += 1;
	len++;
	len = ret - len;
	storage = malloc(sizeof(char) * (len + 1));
	ft_memcpy(storage, temp + *index, len);
	storage[len + 1] = '\0';
	*buff = malloc(sizeof(char) * (len + 1));
	if (!*buff || len < 1)
	{
		free(storage);
		return ;
	}
	ft_memcpy(*buff, storage, len + 1);
	free(storage);
}

char	*build_str(char *storage, char *temp,unsigned int ret, int *trigger)
{
	static int	index = 0;
	char		*str;
	char		c;
	int			i;

	i = 0;
	c = temp[i];
	str = malloc(sizeof(char) * (index + ret + 1));
	if (!str)
		return(NULL);
	if (storage)
		ft_memcpy(str, storage, index);
	while (i < ret)
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
		i++;
	}
	index += i;
	return (str);
}

char	*read_line(int fd, char **buff, int	*index)
{
	unsigned int		ret;
	char	*temp;
	int		trigger;
	char	*storage;
	char	buf[BUFFER_SIZE];

	trigger = 0;
	storage = NULL;
	ret = read(fd, buf, BUFFER_SIZE);
	if (!ret)
		return (NULL);
	while (ret)
	{
		temp = malloc(sizeof(char) * ft_strlen(storage) + 1);
		if (ft_strlen(storage) != 0)
		{
			ft_memcpy(temp, storage, ft_strlen(storage));			
			temp[ft_strlen(storage) + 1] = '\0';
			free(storage);
		}
		storage = build_str(temp, buf, ret, &trigger);
		free(temp);
		if (trigger == 1)
		{
			// *buff = handle_overflow(ret, buf, index);
			handle_overflow(buff, ret, buf, index);
			*index = 0;
			return (storage);
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (storage);
}

char	*line_from_buff(char **buff, int len)
{
	char	*line;
	char 	*temp;
	int		size;

	size = ft_strlen(*buff) - len;
	line = malloc(sizeof(char) * (len + 2));
	temp = malloc(sizeof(char) * (size + 1));
	if (!line || !temp)
		return (NULL);
	ft_memcpy(line, *buff, len + 1);
	line[len + 1] = '\0';
	ft_memcpy(temp, *buff + len + 1, size);
	temp[size] = '\0';
	free(*buff);
	*buff = malloc(sizeof(char) * (size + 1));
	ft_memcpy(*buff, temp, size + 1);
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buff;
	static int	index;
	char		*line;
	char		*storage;
	char		*temp;
	int			len;

	len = 0;
	if (buff)
	{
		if (ft_memchr(buff, '\n', ft_strlen(buff)))
		{
			while (buff[len] != '\n')
				len++;
			line = line_from_buff(&buff, len);
			return (line);
		}
		line = malloc(sizeof(char) * ft_strlen(buff) + 1);
		ft_memcpy(line, buff, ft_strlen(buff) + 1);
		storage = read_line(fd, &buff, &index);
		if (len == 0 && ft_strlen(storage) == 0)
		{
			free(line);
			free(storage);
			return (NULL);
		}
		// printf("-----line = %s storage = %s-----\n", line, storage);
		temp = ft_strjoin(line, storage);
		free(line);
		free(storage);
		return (temp);
	}
	else
		storage = read_line(fd, &buff, &index);
	return (storage);
}

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
	while (line != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}