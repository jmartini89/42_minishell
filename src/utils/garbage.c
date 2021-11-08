/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:46 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:47 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_gc_3p_str(char ***heap)
{
	int	i;
	int	j;

	i = 0;
	while (heap[i])
	{
		j = 0;
		while (heap[i][j])
		{
			free (heap[i][j]);
			j++;
		}
		free (heap[i]);
		i++;
	}
	free (heap);
}

void
	ft_gc_2p_str(char **heap)
{
	int	i;

	i = -1;
	while (heap[++i])
		free (heap[i]);
	free (heap);
}

void
	ft_gc_cmd(t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < shell->cmd_cnt)
	{
		j = 0;
		while (shell->cmd[i].argv && shell->cmd[i].argv[j])
		{
			free (shell->cmd[i].argv[j]);
			j++;
		}
		ft_rdr_clear(&shell->cmd[i].redir, free);
		free (shell->cmd[i].argv);
		i++;
	}
	free (shell->cmd);
	shell->cmd = NULL;
}

void
	ft_gc(t_shell *shell)
{
	rl_clear_history();
	ft_gc_2p_str(shell->env);
	free (shell->ret_str);
	shell->ret_str = NULL;
}
