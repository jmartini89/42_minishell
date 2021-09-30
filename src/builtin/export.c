#include "minishell.h"

static void	ft_export_print_env(t_shell *shell)
{
	int	i;

	i = -1;
	while (shell->env[++i])
		ft_printf("%s\n", shell->env[i]);
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
	if (argc == 1)
	{
		ft_export_print_env(shell);
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
