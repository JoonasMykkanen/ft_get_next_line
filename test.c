#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10000000
#endif


size_t	ft_strlen(char const *s, int mode);

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

	str = (char *)malloc(sizeof(char) * (ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1));
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

size_t	ft_strlen(char const *s, int mode)
{
	int	i;

	i = 0;
	if (s == NULL || !s)
		return (0);
	if (mode == 42)
	{
		while (s[i] != '\n')
			i++;
		return (i);
	}
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strldup(char *src, int len)
{
	char	*dst;

	if (len < 1 || !src)
		return (NULL);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, len);
	dst[len] = '\0';
	return (dst);
}

struct s_variables
{
	unsigned int	ho_len;
	int				lfb_size;
	int				bs_i;
	int				gnl_len;
}					var;

static void	handle_overflow(unsigned int ret, char *temp)
{
	char	*storage;

	var.ho_len = -1;
	s.index = 0;
	free(s.buff);
	s.buff = NULL;
	while (temp[++var.ho_len] != '\n' && var.ho_len <= ret)
		s.index += 1;
	s.index += 1;
	var.ho_len++;
	var.ho_len = ret - var.ho_len;
	if (var.ho_len == 0)
		return ;
	storage = ft_strldup(temp + s.index, var.ho_len);
	s.buff = ft_strldup(storage, var.ho_len);
	if (!s.buff || var.ho_len < 1)
	{
		free(storage);
		return ;
	}
	free(storage);
}

static char	*build_str(char *storage, char *temp, int ret, int *trigger)
{
	static int	index = 0;
	char		*buf;

	var.bs_i = -1;
	if (temp == NULL)
		return (ft_strjoin("", storage));
	buf = malloc(index + ret + 2);
	if (!buf)
		return (NULL);
	if (storage)
		ft_memcpy(buf, storage, index);
	while (++var.bs_i < ret)
	{
		buf[index + var.bs_i] = temp[var.bs_i];
		if (temp[var.bs_i] == '\n')
		{
			buf[index + var.bs_i + 1] = '\0';
			*trigger = 1;
			index = 0;
			return (buf);
		}
	}
	buf[index + var.bs_i] = '\0';
	index += var.bs_i;
	return (buf);
}

static char	*read_line(int fd, int ret, char *buf)
{
	char	*temp;
	int		trigger;
	char	*storage;

	trigger = 0;
	storage = NULL;
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
		return (NULL);
	while (ret)
	{
		temp = NULL;
		if (ft_strlen(storage, 0) != 0)
			temp = build_str(storage, NULL, ft_strlen(storage, 0), &trigger);
		free(storage);
		storage = build_str(temp, buf, ret, &trigger);
		free(temp);
		if (trigger == 1)
		{
			handle_overflow(ret, buf);
			return (storage);
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (storage);
}

char	*line_from_buff(int len)
{
	char	*line;
	char	*temp;

	if (ft_memchr(s.buff, '\n', ft_strlen(s.buff, 0)))
		len = ft_strlen(s.buff, 42);
	else
		len = ft_strlen(s.buff, 0);
	var.lfb_size = ft_strlen(s.buff, 0) - (size_t)len;
	line = ft_strldup(s.buff, len + 1);
	if (var.lfb_size > len)
	{
		temp = ft_strldup(s.buff + len + 1, var.lfb_size);
		free(s.buff);
		s.buff = ft_strldup(temp, var.lfb_size);
		free(temp);
		return (line);
	}
	free(s.buff);
	s.buff = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	char		*storage;
	char		*temp;
	char		*line;

	if (s.buff)
	{
		if (ft_memchr(s.buff, '\n', ft_strlen(s.buff, 0)))
			return (line_from_buff(-1));
		temp = line_from_buff(-1);
		storage = read_line(fd, 0, buf);
		if (storage == NULL && ft_strlen(temp, 0) < 1)
		{
			free(temp);
			free(storage);
			return (NULL);
		}
		line = ft_strjoin(temp, storage);
		free(temp);
		free(storage);
		return (line);
	}
	return (read_line(fd, 0, buf));
}


int	main()
{
	int		fd;
	char	*file;
	char 	*line;

	file = "files/alternate_line_nl_no_nl";
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