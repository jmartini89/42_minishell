/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:44:23 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/10 18:44:24 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_debug_parser(t_shell *shell)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (cnt < shell->cmd_cnt)
	{
		i = 0;
		ft_printf("---CMD %d---\n", cnt);
		while (shell->cmd[cnt].argv && shell->cmd[cnt].argv[i])
		{
			ft_printf("WORD\t%s\n", shell->cmd[cnt].argv[i]);
			i++;
		}
		ft_rdr_iter(shell->cmd[cnt].redir, ft_rdr_print);
		ft_printf("-----------\n", cnt);
		cnt++;
	}
}

int
	ft_debug_leaks_at_exit(t_shell *shell)
{
	int	debug;

	debug = ft_atoi(shell->ret_str);
	ft_printf("exit\n");
	ft_gc(shell);
	return (debug);
}
