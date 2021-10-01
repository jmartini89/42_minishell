#include "minishell.h"

int	ft_export_arg_validity(char *arg)
{
	//
}

void	ft_export(t_shell *shell, char **argv)
{
	int		argc;
	char	*tmp;

	argc = 0;
	while (argv[argc])
		argc++;
	if (argc == 1)
	{
		ft_env(shell, NULL);
		return ;
	}
	else
	{
		if (!ft_export_arg_validity(argv[1]))
			/* add */;
		else
			/* getenv */;
		ft_printf("WIP\n");
	}
}
