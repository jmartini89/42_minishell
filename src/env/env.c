#include "minishell.h"

static int	ft_env_dup(char **env)
{
	int		env_len;
	int		i;

	env_len = 0;
	while (env[env_len])
		env_len++;
	i = -1;
	while (++i < env_len)
	{
		env[i] = ft_strdup(env[i]);
		if (!env[i])
			return (ft_perror(ERR_SYS_MALLOC));
	}
	return (1);
}

static int	ft_env_custom(t_shell *shell)
{
	int		i;
	int		shlvl;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	i = -1;
	if (getenv("SHLVL"))
		shlvl = ft_atoi(getenv("SHLVL")) + 1;
	while (shell->env[++i])
	{
		if (!ft_memcmp(shell->env[i], "SHLVL=", 6))
		{
			tmp = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
			tmp2 = ft_strjoin("SHLVL=", tmp);
			free (tmp);
			tmp = shell->env[i];
			shell->env[i] = tmp2;
			free (tmp);
		}
	}
	return (1);
}

int	ft_env_init(t_shell *shell)
{
	if (ft_env_dup(shell->env) < 0)
		return (0);
	if (ft_env_custom(shell) < 0)
		return (0);
	return (1);
}
