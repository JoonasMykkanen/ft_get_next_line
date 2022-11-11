




#include <unistd.h>

int	main()
{
	char	*str;

	str = "Hello World!";

	write(1, &str[4], 1);
	return 0;
}
