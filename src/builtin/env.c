/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:39 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:40 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_env_print(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_printf("%s\n", env[i]);
}

void
	ft_env(t_shell *shell, char **argv, int process)
{
	int	argc;

	argc = ft_argc(argv);
	while (argv && argv[argc])
		argc++;
	if (argc > 1)
	{
		ft_error(ERR_BLTIN_ARGS, NULL);
		ft_env_return(shell, 1);
		if (process)
			exit (ft_atoi(shell->ret_str));
		return ;
	}
	ft_env_print(shell->env);
	ft_env_return(shell, 0);
	if (process)
		exit (ft_atoi(shell->ret_str));
}
