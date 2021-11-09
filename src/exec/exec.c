/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:20 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:21 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ft_single_shot_builtin(t_shell *shell)
{
	int	builtin;

	builtin = ft_builtin_check(shell->cmd[0].argv);
	if (shell->cmd_cnt == 1 && builtin)
	{
		if (shell->cmd[0].redir)
			ft_printf("EXEC REDIRECTION DEBUG\n");
		ft_builtin_launch(shell, shell->cmd[0].argv, builtin, FALSE);
		return (1);
	}
	return (0);
}

static void
	ft_child(t_shell *shell, int i)
{
	int	builtin;
	int	err;

	ft_signal_default();
	builtin = ft_builtin_check(shell->cmd[i].argv);
	if (builtin)
		ft_builtin_launch(shell, shell->cmd[i].argv, builtin, TRUE);
	if (!ft_is_path(shell->cmd[i].argv[0]))
	{
		if (!ft_exec_env_path(shell, &shell->cmd[i].argv[0]))
			ft_error_exit(ERR_EXEC_NOCMD, NULL, 127);
	}
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

static void
	ft_terminator(t_shell *shell, pid_t *pid_arr)
{
	int	wstatus;
	int	wexit;
	int	i;

	i = 0;
	while (i < shell->cmd_cnt)
	{
		wexit = waitpid(pid_arr[i], &wstatus, WUNTRACED);
		if (wexit == -1)
			ft_error_exit(errno, "waitpid", EXIT_FAILURE);
		if (WIFSTOPPED(wstatus))
			ft_env_return(shell, WSTOPSIG(wstatus) + 128);
		if (WIFSIGNALED(wstatus))
		{
			if (WTERMSIG(wstatus) == SIGINT)
				ft_printf("\n");
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
	int		i;
	pid_t	pid;
	pid_t	*pid_arr;

	int		pipefd[2];
	int		read;

	if (ft_single_shot_builtin(shell))
		return ;

	pid_arr = ft_calloc(shell->cmd_cnt, sizeof(*pid_arr));
	if (pid_arr == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);

	i = 0;
	while (i < shell->cmd_cnt)
	{
		if (shell->cmd_cnt > 1 && i + 1 < shell->cmd_cnt)
			if (pipe(pipefd) == -1)
				ft_error_exit(errno, "pipe", EXIT_FAILURE);
		if (shell->cmd[i].argv)
		{
			pid = fork();
			if (pid < 0)
				ft_error_exit(errno, "fork", EXIT_FAILURE);
			if (pid == 0)
			{
				if (shell->cmd_cnt > 1)
				{
					if (i)
					{
						if (dup2(read, STDIN_FILENO) == -1)
							ft_error_exit(errno, "dup2", EXIT_FAILURE);
						if (close(read) == -1)
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
				ft_child(shell, i);
			}
			else
				pid_arr[i] = pid;
		}
		if (shell->cmd_cnt > 1)
		{
			if (i)
				if (close(read) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			read = pipefd[0];
			if (i + 1 < shell->cmd_cnt)
				if (close(pipefd[1]) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
		}
		i++;
	}
	ft_terminator(shell, pid_arr);
	free (pid_arr);
}
