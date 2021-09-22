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

static int	ft_env_custom(t_shell *shell)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	i = -1;
	if (ft_getenv(shell, "SHLVL")) // ELSE EXPORT
	{
		while (shell->env[++i])
		{
			if (!ft_memcmp(shell->env[i], "SHLVL=", 6))
			{
				tmp = ft_itoa(ft_atoi(ft_getenv(shell, "SHLVL")) + 1);
				tmp2 = ft_strjoin("SHLVL=", tmp);
				free (tmp);
				tmp = shell->env[i];
				shell->env[i] = tmp2;
				free (tmp);
			}
		}
	}
	return (1);
}

int	ft_env_init(t_shell *shell, char **envp)
{
	if (ft_env_dup(shell, envp) < 0)
		return (0);
	if (ft_env_custom(shell) < 0)
		return (0);
	return (1);
}
