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

static void	ft_env_custom_lvl(t_shell *shell)
{
	char	**custom;
	char	*itoa;
	char	*tmp;

	custom = ft_calloc(3, sizeof(*custom));
	custom[0] = "export";
	itoa = ft_itoa(ft_atoi(ft_getenv(shell, "SHLVL")) + 1);
	tmp = ft_strjoin("SHLVL=", itoa);
	if (!itoa || !tmp)
		ft_perror_exit(ERR_SYS_MALLOC);
	free (itoa);
	custom[1] = tmp;
	ft_export(shell, custom);
	free (tmp);
	free (custom);
}

int	ft_env_init(t_shell *shell, char **envp)
{
	shell->ret_str = NULL;
	ft_env_return(shell, 0);
	ft_env_dup(shell, envp);
	ft_env_custom_lvl(shell);
	return (1);
}
