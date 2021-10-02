#include "minishell.h"

void	ft_unset_remove(t_shell *shell, char *arg)
{
	char	**tmp;
	int		len;
	int		arg_len;
	int		i;
	int		j;

	tmp = shell->env;
	len = 0;
	while (tmp[len])
		len++;
	shell->env = ft_calloc(len + 1, sizeof(*shell->env));
	if (!shell->env)
		ft_perror_exit(ERR_SYS_MALLOC);
	arg_len = ft_strlen(arg);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (ft_memcmp(arg, tmp[i], arg_len))
		{
			shell->env[j] = ft_strdup(tmp[i]);
			if (!shell->env[j])
				ft_perror_exit(ERR_SYS_MALLOC);
			i++;
			j++;
		}
		else if (!ft_memcmp(arg, tmp[i], arg_len)
			&& tmp[i][arg_len] == '=')
			i++;
	}
	ft_gc_env(tmp);
}

int	ft_unset_engine(t_shell *shell, char *arg)
{
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
			return (0);
	}
	if (ft_getenv(shell, arg))
		ft_unset_remove(shell, arg);
	return (1);
}

void	ft_unset(t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
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
