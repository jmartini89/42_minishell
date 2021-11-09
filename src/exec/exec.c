/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:20 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 17:05:57 by jm & mc          ###   ########.fr       */
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
		// ft_redir(shell->cmd[0].redir);
		ft_builtin_launch(shell, shell->cmd[0].argv, builtin, FALSE);
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
