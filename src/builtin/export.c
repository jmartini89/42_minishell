#include "minishell.h"

static void	ft_export_print_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}

int	ft_export_arg_validity(char *arg)
{
	//
}

int	ft_export(t_shell *shell, char **argv)
{
	int		argc;
	char	*tmp;

	argc = 0;
	while (argv[argc])
		argc++;
	if (!ft_memcmp(argv[0], "env", 3) && ft_strlen(argv[0]) == 3)
	{
		if (argc > 1)
		{
			ft_perror(ERR_BLTIN_ENV);
			return (EXIT_FAILURE);
		}
		ft_export_print_env(shell->env);
		return (EXIT_SUCCESS);
	}
	if (argc == 1)
	{
		ft_export_print_env(shell->env);
		return (EXIT_SUCCESS);
	}
	else
	{
		if (!ft_export_arg_validity(argv[1]))
			/* add */;
		else
			/* getenv */;
		ft_printf("DEBUG\n");
	}
	return (EXIT_SUCCESS);
}
