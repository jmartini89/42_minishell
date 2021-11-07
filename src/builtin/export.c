/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:44 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:45 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_export_change(t_shell *shell, char *arg, char *env_name)
{
	char	*tmp;
	int		len;
	int		i;
	int		env_name_len;

	len = ft_argc(shell->env);
	env_name_len = ft_strlen(env_name);
	i = -1;
	while (++i < len)
	{
		if (!ft_memcmp(env_name, shell->env[i], env_name_len)
			&& shell->env[i][env_name_len]
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
	len = ft_argc(shell->env);
	shell->env = ft_calloc(len + 2, sizeof(*shell->env));
	if (!shell->env)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	i = -1;
	while (++i < len)
		shell->env[i] = tmp[i];
	shell->env[len] = arg;
	free (tmp);
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
				ft_error_exit(errno, "malloc", EXIT_FAILURE);
			ft_memcpy(env_name, arg, i);
			arg_heap = ft_strdup(arg);
			if (!arg_heap)
				ft_error_exit(errno, "malloc", EXIT_FAILURE);
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
			ft_error(ERR_BLTIN_EXPORT, NULL);
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
