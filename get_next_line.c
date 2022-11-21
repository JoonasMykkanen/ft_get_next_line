/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 10:26:24 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 10:26:24 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	storage = ft_calloc(var.ho_len + 1, 1);
	ft_memcpy(storage, temp + s.index, var.ho_len);
	storage[var.ho_len] = '\0';
	s.buff = ft_calloc(var.ho_len + 1, 1);
	if (!s.buff || var.ho_len < 1)
	{
		free(storage);
		return ;
	}
	ft_memcpy(s.buff, storage, var.ho_len + 1);
	free(storage);
}

static char	*build_str(char *storage, char *temp, int ret, int *trigger)
{
	static int	index = 0;
	char		*buf;

	var.bs_i = -1;
	if (temp == NULL)
		return (ft_strjoin("", storage));
	buf = ft_calloc(index + ret + 2, 1);
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
		if (ft_strlen(storage) != 0)
			temp = build_str(storage, NULL, ft_strlen(storage), &trigger);
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

	if (ft_memchr(s.buff, '\n', ft_strlen(s.buff)))
	{
		while (s.buff[++len] != '\n')
			;
	}
	var.lfb_size = ft_strlen(s.buff) - (size_t)len;
	line = ft_calloc(len + 2, 1);
	ft_memcpy(line, s.buff, len + 1);
	line[len + 1] = '\0';
	if (var.lfb_size > len)
	{
		temp = ft_calloc(var.lfb_size + 1, 1);
		ft_memcpy(temp, s.buff + len + 1, var.lfb_size);
		temp[var.lfb_size] = '\0';
		free(s.buff);
		s.buff = ft_calloc(var.lfb_size + 1, 1);
		ft_memcpy(s.buff, temp, var.lfb_size + 1);
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
		var.gnl_len = ft_strlen(s.buff);
		line = line_from_buff(var.gnl_len);
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
