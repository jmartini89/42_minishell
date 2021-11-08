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

static void
	ft_child(t_shell *shell, int i)
{
	int	builtin;
	int	err;

	ft_signal_default();
	builtin = ft_builtin_check(shell->cmd[i].argv);
	if (builtin)
		ft_builtin_launch(shell, shell->cmd[i].argv, builtin, TRUE);
	else if (!ft_is_path(shell->cmd[i].argv[0]))
		if (!ft_exec_env_path(shell, &shell->cmd[i].argv[0]))
			ft_error_exit(ERR_EXEC_NOCMD, NULL, 127);
	if (execve(shell->cmd[i].argv[0], shell->cmd[i].argv, shell->env) == -1)
	{
		err = errno;
		rl_clear_history();
		if (err == ENOENT)
			ft_error_exit(ERR_EXEC_NOFILE, NULL, 127);
		if (err == EACCES)
			ft_error_exit(ERR_EXEC_PERM, NULL, 126);
		else
			ft_error_exit(ERR_EXEC_UNKWN, NULL, EXIT_FAILURE);
	}
}

void
	ft_exec(t_shell *shell)
{
	int		builtin;
	pid_t	pid;
	pid_t	*pid_arr;
	int		wstatus;
	int		wexit;
	int		i;

	builtin = ft_builtin_check(shell->cmd[0].argv);
	if (shell->cmd_cnt == 1 && builtin)
	{
		if (shell->cmd[0].redir)
			ft_printf("EXEC REDIRECTION DEBUG\n");
		ft_builtin_launch(shell, shell->cmd[0].argv, builtin, FALSE);
		return ;
	}

	pid_arr = ft_calloc(shell->cmd_cnt, sizeof(*pid_arr));
	if (pid_arr == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);

	i = 0;
	while (i < shell->cmd_cnt)
	{
		if ((i + 1) < shell->cmd_cnt)
			printf("PIPE R DETECTED\n");
		if (i)
			printf("PIPE L DETECTED\n");
		if (shell->cmd[i].argv)
		{
			pid = fork();
			if (pid < 0)
				ft_error_exit(errno, "fork", EXIT_FAILURE);
			if (pid == 0)
				ft_child(shell, i);
			else
				pid_arr[i] = pid;
		}
		i++;
	}
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
			ft_printf("\n");
			ft_env_return(shell, WTERMSIG(wstatus) + 128);
		}
		if (WIFEXITED(wstatus))
			ft_env_return(shell, WEXITSTATUS(wstatus));
		i++;
	}
	free (pid_arr);
}
