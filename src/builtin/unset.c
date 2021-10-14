#include "minishell.h"

static void
	ft_unset_remove_supp(t_shell *shell, char *arg, char **tmp)
{
	int	arg_len;
	int	i;
	int	j;

	arg_len = ft_strlen(arg);
	i = -1;
	j = 0;
	while (tmp[++i])
	{
		if (ft_memcmp(arg, tmp[i], arg_len))
		{
			shell->env[j] = ft_strdup(tmp[i]);
			if (!shell->env[j])
				ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
			j++;
		}
	}
}

static void
	ft_unset_remove(t_shell *shell, char *arg)
{
	char	**tmp;
	int		len;

	tmp = shell->env;
	len = 0;
	while (tmp[len])
		len++;
	shell->env = ft_calloc(len + 1, sizeof(*shell->env));
	if (!shell->env)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	ft_unset_remove_supp(shell, arg, tmp);
	ft_gc_arr_str(tmp);
}

static int
	ft_unset_engine(t_shell *shell, char *arg)
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

void
	ft_unset(t_shell *shell, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_unset_engine(shell, argv[i]))
		{
			ft_perrno(ERR_BLTIN_UNSET, NULL);
			ft_env_return(shell, 1);
			return ;
		}
		i++;
	}
	ft_env_return(shell, 0);
}
