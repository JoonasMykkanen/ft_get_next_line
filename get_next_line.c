
#include "get_next_line.h"

static void	handle_overflow(unsigned int ret, char *temp)
{
	unsigned int	len;
	char 			*storage;

	len = 0;
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
	char		*str;
	int			i;	

	i = -1;
	str = malloc(sizeof(char) * (index + ret + 2));
	if (!str)
		return(NULL);
	if (storage)
		ft_memcpy(str, storage, index);
	while (++i < ret)
	{
		str[index + i] = temp[i];
		if (temp[i] == '\n')
		{
			str[index + i + 1] = '\0';
			*trigger = 1;
			index = 0;
			return (str);
		}
	}
	str[index + i] = '\0';
	index += i;
	return (str);
}

static char	*read_line(int fd)
{
	int		ret;
	char	*temp;
	int		trigger;
	char	*storage;
	char	buf[BUFFER_SIZE];

	trigger = 0;
	storage = NULL;
	ret = read(fd, buf, BUFFER_SIZE);
	if (ret == -1)
		return (NULL);
	while (ret)
	{
		temp = malloc(sizeof(char) * ft_strlen(storage) + 2); //mby move to if statement
		if (ft_strlen(storage) != 0)
		{
			ft_memcpy(temp, storage, ft_strlen(storage));			
			temp[ft_strlen(storage) + 1] = '\0';
			free(storage);
			storage = NULL;
		}
		storage = build_str(temp, buf, ret, &trigger);
		free(temp);
		if (trigger == 1)
		{
			handle_overflow(ret, buf);
			s.index = 0;
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
	char		*line;
	char		*storage;
	char		*temp;
	int			len;

	len = -1;
	if (s.buff)
	{
		if (ft_memchr(s.buff, '\n', ft_strlen(s.buff)))
			return (line_from_buff(len));
		line = line_from_buff(len);
		storage = read_line(fd);
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
	return (read_line(fd));
}