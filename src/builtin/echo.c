#include "minishell.h"

void
	ft_echo(t_shell *shell, char **argv)
{
	int	i;
	int	newline;

	newline = 1;
	i = 1;
	while (argv[i] && !ft_memcmp(argv[i], "-n", 2) && ft_strlen(argv[i]) == 2)
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_printf("%s", argv[i]);
		i++;
		if (argv[i])
			ft_printf(" ");
	}
	if (newline)
		ft_printf("\n");
	ft_env_return(shell, 0);
}
