/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:03:21 by jmykkane          #+#    #+#             */
/*   Updated: 2022/11/22 09:03:25 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	handle_overflow(unsigned int ret, char *temp, char **buff)
{
	char		*storage;
	static int	index;
	int			len;

	len = -1;
	index = 0;
	free(*buff);
	*buff = NULL;
	while (temp[++len] != '\n' && len <= (int)ret)
		index += 1;
	index += 1;
	len++;
	len = ret - len;
	if (len == 0)
		return ;
	storage = ft_strldup(temp + index, len);
	*buff = ft_strldup(storage, len);
	if (!*buff || len < 1)
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
	int			i;

	i = -1;
	if (temp == NULL)
		return (ft_strjoin("", storage));
	buf = malloc(index + ret + 2);
	if (!buf)
		return (NULL);
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

static char	*read_line(int fd, int ret, char *buf, char **buff)
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
			handle_overflow(ret, buf, buff);
			return (storage);
		}
		ret = read(fd, buf, BUFFER_SIZE);
	}
	return (storage);
}

char	*line_from_buff(int len, char **buff)
{
	char	*line;
	char	*temp;
	int		size;

	if (ft_memchr(*buff, '\n', ft_strlen(*buff, 0)))
		len = ft_strlen(*buff, 42);
	else
		len = ft_strlen(*buff, 0);
	size = ft_strlen(*buff, 0) - (size_t)len;
	line = ft_strldup(*buff, len + 1);
	if (size > 0)
	{
		temp = ft_strldup(*buff + len + 1, size);
		free(*buff);
		*buff = ft_strldup(temp, size);
		free(temp);
		return (line);
	}
	free(*buff);
	*buff = NULL;
	return (line);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE];
	char		*storage;
	char		*temp;
	char		*line;
	static char	*buff;

	if (buff)
	{
		if (ft_memchr(buff, '\n', ft_strlen(buff, 0)))
			return (line_from_buff(-1, &buff));
		temp = line_from_buff(-1, &buff);
		storage = read_line(fd, 0, buf, &buff);
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
	return (read_line(fd, 0, buf, &buff));
}
