/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:20 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 17:15:51 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_newline_sigint(int wstatus, int *newline)
{
	if (WTERMSIG(wstatus) == SIGINT && *newline == 0)
	{
		*newline = *newline + 1;
		ft_printf("\n");
	}
}

static void
	ft_wait(t_shell *shell, pid_t *pid_arr, int cnt)
{
	int	wstatus;
	int	wexit;
	int	newline;
	int	i;

	newline = 0;
	i = 0;
	while (i < cnt)
	{
		wexit = waitpid(pid_arr[i], &wstatus, WUNTRACED);
		if (wexit == -1)
			ft_error_exit(errno, "waitpid", EXIT_FAILURE);
		if (WIFSTOPPED(wstatus))
			ft_env_return(shell, WSTOPSIG(wstatus) + 128);
		if (WIFSIGNALED(wstatus))
		{
			ft_newline_sigint(wstatus, &newline);
			ft_env_return(shell, WTERMSIG(wstatus) + 128);
		}
		if (WIFEXITED(wstatus))
			ft_env_return(shell, WEXITSTATUS(wstatus));
		i++;
	}
}

void
	ft_exec(t_shell *shell)
{
	pid_t	*pid_arr;
	int		cnt;

	if (ft_builtin_as_parent(shell))
		return ;
	pid_arr = ft_calloc(shell->cmd_cnt, sizeof(*pid_arr));
	if (pid_arr == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	cnt = ft_fork(shell, pid_arr);
	ft_wait(shell, pid_arr, cnt);
	free (pid_arr);
}
