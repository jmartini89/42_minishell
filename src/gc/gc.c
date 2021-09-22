#include "minishell.h"

void	ft_gc_token(char **token)
{
	int	i;

	i = -1;
	while (token[++i])
		free (token[i]);
	free (token);
	token = NULL;
}

void	ft_gc_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		free (env[i]);
	free (env);
	env = NULL;
}

void	ft_gc(t_shell *shell)
{
	ft_gc_env(shell->env);
}
