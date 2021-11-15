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

static int
	ft_is_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_isdigit(arg[i]) == FALSE
			&& arg[i] != '+'
			&& arg[i] != '-')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

void
	ft_exit(t_shell *shell, char **argv, int process)
{
	int	argc;
	int	status;

	status = ft_atoi(shell->ret_str);
	if (process == FALSE)
		ft_printf("exit\n");
	argc = ft_argc(argv);
	if (argc > 1)
	{
		if (ft_is_numeric(argv[1]) == FALSE)
			ft_error_exit(ERR_BLTIN_EXIT_NUM, NULL, 2);
		if (argc > 2)
			ft_error_exit(ERR_BLTIN_EXIT_ARGS, NULL, 1);
		status = ft_atoi(argv[1]) & 0xFF;
	}
	exit (status);
}
