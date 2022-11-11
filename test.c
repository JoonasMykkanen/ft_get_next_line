

#include <stdio.h>

void	math(int *trigger)
{
	*trigger = 1;
}




#include <unistd.h>

int	main()
{
	char	*str;
	int	trigger = 0;
	


	math(&trigger);
	printf("%d", trigger);


	str = "Hello World!";

	write(1, &str[4], 1);
	return 0;
}
