/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:50 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:51 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_unset_remove_supp(t_shell *shell, char *arg, char **tmp)
{
	int	arg_len;
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (tmp[++i])
	{
		arg_len = ft_lencmp(arg, tmp[i]);
		if (ft_memcmp(arg, tmp[i], arg_len))
		{
			shell->env[j] = tmp[i];
			j++;
		}
		else
			free (tmp[i]);
	}
}

static void
	ft_unset_remove(t_shell *shell, char *arg)
{
	char	**tmp;
	int		len;

	tmp = shell->env;
	len = ft_argc(tmp);
	shell->env = ft_calloc(len + 1, sizeof(*shell->env));
	if (!shell->env)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	ft_unset_remove_supp(shell, arg, tmp);
	free (tmp);
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
	ft_unset(t_shell *shell, char **argv, int process)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (!ft_unset_engine(shell, argv[i]))
		{
			ft_error(ERR_BLTIN_UNSET, NULL);
			ft_env_return(shell, 1);
			if (process)
				exit (ft_atoi(shell->ret_str));
			return ;
		}
		i++;
	}
	ft_env_return(shell, 0);
	if (process)
		exit (ft_atoi(shell->ret_str));
}
