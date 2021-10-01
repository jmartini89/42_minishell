#include "minishell.h"

void	ft_env_print(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}

void	ft_env(t_shell *shell, char **argv)
{
	int	argc;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	if (argc > 1)
	{
		ft_perror(ERR_BLTIN_ENV);
		ft_env_return(shell, 1);
		return ;
	}
	ft_env_print(shell->env);
	ft_env_return(shell, 0);
}
