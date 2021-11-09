/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:42 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:43 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_exit(t_shell *shell, char **argv, int process)
{
	int	argc;

	argc = ft_argc(argv);
	if (argc > 1)
	{
		ft_error(ERR_BLTIN_ARGS, NULL);
		ft_env_return(shell, 1);
		if (process)
			exit (ft_atoi(shell->ret_str));
		return ;
	}
	if (process == FALSE)
		ft_printf("exit\n");
	exit (ft_atoi(shell->ret_str));
}
