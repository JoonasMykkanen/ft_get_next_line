

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 30
#endif

#include <stdlib.h>
#include <sys/uio.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd);
size_t	ft_strlen(char const *s);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif
