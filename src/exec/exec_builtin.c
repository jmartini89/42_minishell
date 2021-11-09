/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:16 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:17 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_fd_reset(t_cmd *cmd, int *io)
{
	if (cmd->r_in)
		if (dup2(io[0], STDIN_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
	if (cmd->r_out)
		if (dup2(io[1], STDOUT_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
	if (close(io[0]) == -1)
		ft_error_exit(errno, "close", EXIT_FAILURE);
	if (close(io[1]) == -1)
		ft_error_exit(errno, "close", EXIT_FAILURE);
}

int
	ft_builtin_as_parent(t_shell *shell)
{
	int	builtin;
	int	io[2];

	builtin = ft_builtin_check(shell->cmd[0].argv);
	if (shell->cmd_cnt == 1 && builtin)
	{
		io[0] = dup(STDIN_FILENO);
		if (io[0] == -1)
			ft_error_exit(errno, "dup", EXIT_FAILURE);
		io[1] = dup(STDOUT_FILENO);
		if (io[1] == -1)
			ft_error_exit(errno, "dup", EXIT_FAILURE);
		if (!ft_redir(shell, &shell->cmd[0]))
			return (1);
		ft_builtin_launch(shell, shell->cmd[0].argv, builtin, FALSE);
		ft_fd_reset(&shell->cmd[0], io);
		return (1);
	}
	return (0);
}

void
	ft_builtin_launch(t_shell *shell, char **argv, int status, int process)
{
	if (status == (BLTIN_CD))
		ft_cd(shell, argv, process);
	if (status == (BLTIN_ECHO))
		ft_echo(shell, argv, process);
	if (status == (BLTIN_ENV))
		ft_env(shell, argv, process);
	if (status == (BLTIN_EXIT))
		ft_exit(shell, argv, process);
	if (status == (BLTIN_EXPORT))
		ft_export(shell, argv, process);
	if (status == (BLTIN_PWD))
		ft_pwd(shell, argv, process);
	if (status == (BLTIN_UNSET))
		ft_unset(shell, argv, process);
}

int
	ft_builtin_check(char **argv)
{
	int	status;

	status = 0;
	if (argv == NULL)
		return (status);
	if (!ft_memcmp(argv[0], "cd", 2) && ft_strlen(argv[0]) == 2)
		status = (BLTIN_CD);
	if (!ft_memcmp(argv[0], "echo", 4) && ft_strlen(argv[0]) == 4)
		status = (BLTIN_ECHO);
	if (!ft_memcmp(argv[0], "env", 3) && ft_strlen(argv[0]) == 3)
		status = (BLTIN_ENV);
	if (!ft_memcmp(argv[0], "exit", 4) && ft_strlen(argv[0]) == 4)
		status = (BLTIN_EXIT);
	if (!ft_memcmp(argv[0], "export", 6) && ft_strlen(argv[0]) == 6)
		status = (BLTIN_EXPORT);
	if (!ft_memcmp(argv[0], "pwd", 3) && ft_strlen(argv[0]) == 3)
		status = (BLTIN_PWD);
	if (!ft_memcmp(argv[0], "unset", 5) && ft_strlen(argv[0]) == 5)
		status = (BLTIN_UNSET);
	return (status);
}
