#include "minishell.h"

void	ft_unset_remove(t_shell *shell, char *arg)
{
	char	**tmp;
	int		len;
	int		i;
	int		arg_len;

	tmp = shell->env;
	len = 0;
	while (tmp[len])
		len++;
	shell->env = ft_calloc(len, sizeof(*shell->env));
	arg_len = ft_strlen(arg);
	i = 0;
	while (i < len)
	{
		if (!ft_memcmp)
		shell->env[i] = ft_strdup(tmp[i]);
		if (!shell->env[i])
			ft_perror_exit(ERR_SYS_MALLOC);
		i++;
	}
	ft_gc_env(tmp);
}

int	ft_unset_engine(t_shell *shell, char *arg)
{
	char	*env_name;
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return 0;
	}
	if (!ft_getenv(shell, env_name))
		ft_unset_remove(shell, arg);
	return (1);
}

void	ft_unset(t_shell *shell, char **argv)
{
	int	i;

	i = 1;
	if (argv[i])
	{
		if (!ft_unset_engine(shell, argv[i]))
		{
			ft_perror(ERR_BLTIN_UNSET);
			ft_env_return(shell, 1);
			return ;
		}
		i++;
	}
	ft_env_return(shell, 0);
}
