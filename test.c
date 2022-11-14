
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"
#include <string.h>
#include <stdio.h>


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

size_t	ft_strlen(char const *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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
	str[++i] = '\0';	
	return (str);
}


int main () {
   char *s1 = "Test";
   char *s2 = NULL;

   char *s3 = malloc(sizeof(char) * 50);
   s3 = ft_strjoin(s2, s1);
   printf("%s", s3);
   
   return(0);
}
