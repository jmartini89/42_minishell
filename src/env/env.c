#include "minishell.h"

void	ft_env_return(t_shell *shell, int ret)
{
	free (shell->ret_str);
	shell->ret_str = ft_itoa(ret);
	if (!shell->ret_str)
		ft_perror_exit(ERR_SYS_MALLOC);
}

static void	ft_env_dup(t_shell *shell, char **envp)
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
			ft_perror_exit(ERR_SYS_MALLOC);
	}
}

static void	ft_env_custom(t_shell *shell)
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
				if (!tmp || !tmp2)
					ft_perror_exit(ERR_SYS_MALLOC);
				free (tmp);
				tmp = shell->env[i];
				shell->env[i] = tmp2;
				free (tmp);
			}
		}
	}
}

int	ft_env_init(t_shell *shell, char **envp)
{
	shell->ret_str = NULL;
	ft_env_return(shell, 0);
	ft_env_dup(shell, envp);
	ft_env_custom(shell);
	return (1);
}
