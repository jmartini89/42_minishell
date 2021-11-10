/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:02:36 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 17:21:08 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_child_pipe(t_shell *shell, int i, int *pipefd, int input)
{
	if (shell->cmd_cnt > 1)
	{
		if (i)
		{
			if (dup2(input, STDIN_FILENO) == -1)
				ft_error_exit(errno, "dup2", EXIT_FAILURE);
			if (close(input) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
		}
		if (i + 1 < shell->cmd_cnt)
		{
			if (dup2(pipefd[1], STDOUT_FILENO) == -1)
				ft_error_exit(errno, "dup2", EXIT_FAILURE);
			if (close(pipefd[1]) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
			if (close(pipefd[0]) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
		}
	}
}

static void
	ft_child_execve(t_shell *shell, int i)
{
	int	err;

	ft_signal_default();
	if (execve(shell->cmd[i].argv[0], shell->cmd[i].argv, shell->env) == -1)
	{
		err = errno;
		rl_clear_history();
		if (err == ENOENT)
			ft_error_exit(err, "execve", 127);
		if (err == EACCES)
			ft_error_exit(err, "execve", 126);
		else
			ft_error_exit(err, "execve", EXIT_FAILURE);
	}
}

void
	ft_child(t_shell *shell, int i, int *pipefd, int input)
{
	int	builtin;

	ft_child_pipe(shell, i, pipefd, input);
	if (!ft_redir(shell, shell->cmd[i].redir))
		ft_exit(shell, NULL, TRUE);
	if (shell->cmd[i].argv == NULL)
		ft_exit(shell, NULL, TRUE);
	builtin = ft_builtin_check(shell->cmd[i].argv);
	if (builtin)
		ft_builtin_launch(shell, shell->cmd[i].argv, builtin, TRUE);
	if (!ft_is_path(shell->cmd[i].argv[0]))
	{
		if (!ft_exec_env_path(shell, &shell->cmd[i].argv[0]))
			ft_error_exit(ERR_EXEC_NOCMD, NULL, 127);
	}
	ft_child_execve(shell, i);
}
