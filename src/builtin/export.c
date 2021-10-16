#include "minishell.h"

static void
	ft_export_change(t_shell *shell, char *arg, char *env_name)
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

static void
	ft_export_add(t_shell *shell, char *arg)
{
	char	**tmp;
	int		len;
	int		i;

	tmp = shell->env;
	len = 0;
	while (tmp[len])
		len++;
	shell->env = ft_calloc(len + 2, sizeof(*shell->env));
	if (!shell->env)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	i = -1;
	while (++i < len)
	{
		shell->env[i] = ft_strdup(tmp[i]);
		if (!shell->env[i])
			ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	}
	shell->env[len] = arg;
	ft_gc_arr_str(tmp);
}

static void
	ft_export_choice(t_shell *shell, char *arg, char *env_name)
{
	if (!ft_getenv(shell, env_name))
		ft_export_add(shell, arg);
	else
		ft_export_change(shell, arg, env_name);
	free (env_name);
}

static int
	ft_export_engine(t_shell *shell, char *arg)
{
	char	*env_name;
	char	*arg_heap;
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '=')
		{
			if (!i)
				return (0);
			env_name = ft_calloc(i + 1, sizeof(*env_name));
			if (!env_name)
				ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
			ft_memcpy(env_name, arg, i);
			arg_heap = ft_strdup(arg);
			if (!arg_heap)
				ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
			ft_export_choice(shell, arg_heap, env_name);
		}
	}
	return (1);
}

void
	ft_export(t_shell *shell, char **argv, int process)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!ft_export_engine(shell, argv[i]))
		{
			ft_perrno(ERR_BLTIN_EXPORT, NULL);
			ft_env_return(shell, 1);
			if (process)
				exit (ft_atoi(shell->ret_str));
			return ;
		}
		i++;
	}
	if (i == 1)
	{
		ft_env(shell, NULL, 0);
		return ;
	}
	ft_env_return(shell, 0);
	if (process)
		exit (ft_atoi(shell->ret_str));
}
