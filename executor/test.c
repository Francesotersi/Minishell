#include "executor.h"

int	main()
{
	static int	fds[30];
	int			i;

	i = 0;
	while (i != 8)
	{
		fds[i] = open("execute.c", O_RDONLY);
		if (fds[i] == -1)
			return (printf("gay"));
		i++;
	}
	i = 0;
	while (fds[i])
		printf("\nfd %d", fds[i++]);
	return (printf("\nEtero"));
}