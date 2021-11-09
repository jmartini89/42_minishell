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

static int
	ft_single_shot_builtin(t_shell *shell)
{
	int	builtin;
	int	out;
	int	in;

	builtin = ft_builtin_check(shell->cmd[0].argv);
	if (shell->cmd_cnt == 1 && builtin)
	{
		in = dup(STDIN_FILENO);
		if (in == -1)
			ft_error_exit(errno, "dup", EXIT_FAILURE);
		out = dup(STDOUT_FILENO);
		if (out == -1)
			ft_error_exit(errno, "dup", EXIT_FAILURE);

		if (!ft_redir(&shell->cmd[0]))
		{
			ft_env_return(shell, EXIT_FAILURE);
			return (1);
		}

		ft_builtin_launch(shell, shell->cmd[0].argv, builtin, FALSE);

		if (shell->cmd[0].r_in)
			if (dup2(in, STDIN_FILENO) == -1)
				ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (shell->cmd[0].r_out)
			if (dup2(out, STDOUT_FILENO) == -1)
				ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(in) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
		if (close(out) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
		return (1);
	}
	return (0);
}

static void
	ft_wait(t_shell *shell, pid_t *pid_arr)
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
	pid_t	*pid_arr;

	signal(SIGINT, SIG_IGN);
	if (ft_single_shot_builtin(shell))
		return ;
	pid_arr = ft_calloc(shell->cmd_cnt, sizeof(*pid_arr));
	if (pid_arr == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	ft_do_exec(shell, pid_arr);
	ft_wait(shell, pid_arr);
	free (pid_arr);
	signal(SIGINT, ft_sig_int);
}
