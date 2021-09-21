#include "minishell.h"

static void	ft_gc_env(char	**env)
{
	int	i;

	i = -1;
	while (env[++i])
		free (env[i]);
}

void	ft_gc(t_shell *shell)
{
	ft_gc_env(shell->env);
}
