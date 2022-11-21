#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h> 
# include <sys/uio.h>
# include <sys/types.h>

static struct s_static
{
	int		index;
	char	*buff;
}			s;

// struct	s_variables
// {
// 	unsigned int	ho_len;
// 	int				lfb_size;
// 	int				bs_i;
// }					s_var;

char	*get_next_line(int fd);
char	*ft_strldup(char *src, int len);
size_t	ft_strlen(char const *s, int mode);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memchr(const void *s, int c, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif