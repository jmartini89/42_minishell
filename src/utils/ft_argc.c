#include "minishell.h"

int
	ft_argc(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}