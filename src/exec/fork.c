/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:02:34 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 23:29:11 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_pipe_new(t_shell *shell, int i, int *pipefd)
{
	if (shell->cmd_cnt > 1 && i + 1 < shell->cmd_cnt)
		if (pipe(pipefd) == -1)
			ft_error_exit(errno, "pipe", EXIT_FAILURE);
}

static void
	ft_pipe_control(t_shell *shell, int i, int *pipefd, int *input)
{
	if (shell->cmd_cnt > 1)
	{
		if (i)
			if (close(*input) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
		*input = pipefd[0];
		if (i + 1 < shell->cmd_cnt)
			if (close(pipefd[1]) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
	}
}

int
	ft_fork(t_shell *shell, pid_t *pid_arr)
{
	int		i;
	pid_t	pid;
	int		pipefd[2];
	int		input;

	input = -1;
	i = 0;
	while (i < shell->cmd_cnt)
	{
		ft_pipe_new(shell, i, pipefd);
		if (!ft_heredoc(shell, shell->cmd[i].redir))
			return (i);
		pid = fork();
		if (pid == -1)
			ft_error_exit(errno, "fork", EXIT_FAILURE);
		if (pid == 0)
			ft_child(shell, i, pipefd, input);
		else
			pid_arr[i] = pid;
		ft_pipe_control(shell, i, pipefd, &input);
		i++;
	}
	return (i);
}
