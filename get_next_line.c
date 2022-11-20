
#include "get_next_line.h"

static void	handle_overflow(unsigned int ret, char *temp)
{
	unsigned int	len;
	char 			*storage;

	len = 0;
	s.index = 0;
	free(s.buff);
	s.buff = NULL;
	while (temp[len] != '\n' && len <= ret)
	{
		s.index += 1;
		len++;
	}
	s.index += 1;
	len++;
	len = ret - len;
	if (len == 0)
		return ;
	storage = malloc(sizeof(char) * (len + 1));
	ft_memcpy(storage, temp + s.index, len);
	storage[len] = '\0';
	s.buff = malloc(sizeof(char) * (len + 1));
	if (!s.buff || len < 1)
	{
		free(storage);
		return ;
	}
	ft_memcpy(s.buff, storage, len + 1);
	free(storage);
}

static char	*build_str(char *storage, char *temp, int ret, int *trigger)
{
	static int	index = 0;
	char		*buf;
	int			i;	

	i = -1;
	if (ft_strncmp(temp, "42", 2) == 0)
		return (ft_strjoin("", storage));
	buf = malloc(sizeof(char) * (index + ret + 2));
	if (!buf)
		return(NULL);
	if (storage)
		ft_memcpy(buf, storage, index);
	while (++i < ret)
	{
		buf[index + i] = temp[i];
		if (temp[i] == '\n')
		{
			buf[index + i + 1] = '\0';
			*trigger = 1;
			index = 0;
			return (buf);
		}
	}
	buf[index + i] = '\0';
	index += i;
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
		if (ft_strlen(storage) != 0)
			temp = build_str(storage, "42", ft_strlen(storage), &trigger);
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
	char 	*temp;
	int		size;

	if (ft_memchr(s.buff, '\n', ft_strlen(s.buff)))
		while (s.buff[++len] != '\n');
	else
		len = ft_strlen(s.buff);
	size = ft_strlen(s.buff) - (size_t)len;
	line = malloc(sizeof(char) * (len + 2));
	ft_memcpy(line, s.buff, len + 1);
	line[len + 1] = '\0';
	if (size > len)
	{
		temp = malloc(sizeof(char) * (size + 1));
		ft_memcpy(temp, s.buff + len + 1, size);
		temp[size] = '\0';
		free(s.buff);
		s.buff = malloc(sizeof(char) * (size + 1));
		ft_memcpy(s.buff, temp, size + 1);
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
	char		*line;
	char		*temp;

	if (s.buff)
	{
		if (ft_memchr(s.buff, '\n', ft_strlen(s.buff)))
			return (line_from_buff(-1));
		line = line_from_buff(-1);
		storage = read_line(fd, 0, buf);
		if (storage == NULL && ft_strlen(line) < 1)
		{
			free(line);
			free(storage);
			return (NULL);
		}
		temp = ft_strjoin(line, storage);
		free(line);
		free(storage);
		return (temp);
	}
	return (read_line(fd, 0, buf));
}
