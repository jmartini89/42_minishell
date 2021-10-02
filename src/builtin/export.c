#include "minishell.h"

static void	ft_export_change(t_shell *shell, char *arg, char *env_name)
{
	char	*tmp;
	int		len;
	int		i;
	int		env_name_len;

	len = 0;
	while (shell->env[len])
		len++;
	env_name_len = ft_strlen(env_name);
	i = -1;
	while (++i < len)
	{
		if (!ft_memcmp(env_name, shell->env[i], env_name_len)
			&& shell->env[i][env_name_len] == '=')
		{
			tmp = shell->env[i];
			shell->env[i] = arg;
			free (tmp);
		}
	}
}

static void	ft_export_add(t_shell *shell, char *arg)
{
	char	**tmp;
	int		len;
	int		i;

	tmp = shell->env;
	len = 0;
	while (tmp[len])
		len++;
	shell->env = ft_calloc(len + 2, sizeof(*shell->env));
	i = -1;
	while (++i < len)
	{
		shell->env[i] = ft_strdup(tmp[i]);
		if (!shell->env[i])
			ft_perror_exit(ERR_SYS_MALLOC);
	}
	shell->env[len] = arg;
	ft_gc_env(tmp);
}

static void	ft_export_engine(t_shell *shell, char *arg)
{
	char	*env_name;
	char	*arg_heap;
	int		i;

	i = 0;
	while (arg[i])
	{
		i++;
		if (arg[i] == '=')
		{
			env_name = ft_calloc(i, sizeof(*env_name));
			if (!env_name)
				ft_perror_exit(ERR_SYS_MALLOC);
			ft_memcpy(env_name, arg, i);
			arg_heap = ft_strdup(arg);
			if (!arg_heap)
				ft_perror_exit(ERR_SYS_MALLOC);
			if (!ft_getenv(shell, env_name))
				ft_export_add(shell, arg_heap);
			else
				ft_export_change(shell, arg_heap, env_name);
			free (env_name);
		}
	}
}

void	ft_export(t_shell *shell, char **argv)
{
	char	*tmp;
	int		i;

	i = 1;
	while (argv[i])
	{
		ft_export_engine(shell, argv[i]);
		i++;
	}
	if (i == 1)
	{
		ft_env(shell, NULL);
		return ;
	}
	ft_env_return(shell, 0);
}
