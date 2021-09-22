#include "minishell.h"

static int	ft_env_dup(t_shell *shell, char **envp)
{
	int		len;
	int		i;

	len = 0;
	while (envp[len])
		len++;
	shell->env = ft_calloc(len + 1, sizeof(*shell->env));
	i = -1;
	while (++i < len)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			return (ft_perror(ERR_SYS_MALLOC));
	}
	return (1);
}

static int	ft_env_custom(char **env)
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
	while (env[++i])
	{
		if (!ft_memcmp(env[i], "SHLVL=", 6))
		{
			tmp = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
			tmp2 = ft_strjoin("SHLVL=", tmp);
			free (tmp);
			tmp = env[i];
			env[i] = tmp2;
			free (tmp);
		}
	}
	return (1);
}

int	ft_env_init(t_shell *shell, char **envp)
{
	if (ft_env_dup(shell, envp) < 0)
		return (0);
	if (ft_env_custom(shell->env) < 0)
		return (0);
	return (1);
}
