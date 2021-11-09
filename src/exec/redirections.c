/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:29:39 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 17:30:04 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ft_redir_fail(t_shell *shell, t_cmd *cmd, int fd_read, int fd_write)
{
	if (cmd->r_in)
	{
		if (fd_read != -1)
			if (close(fd_read) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	if (cmd->r_out)
	{
		if (fd_write != -1)
			if (close(fd_write) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	ft_env_return(shell, EXIT_FAILURE);
	return (0);
}

int
	ft_redir(t_shell *shell, t_cmd *cmd)
{
	int		fd_read;
	int		fd_write;
	t_redir	*lst;

	cmd->r_in = FALSE;
	cmd->r_out = FALSE;
	lst = cmd->redir;
	if (lst == NULL)
		return (1);
	while (lst)
	{
		if (lst->type == R_OUT)
		{
			if (cmd->r_out == TRUE)
				if (close(fd_write) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_write = open(lst->name, O_CREAT | O_TRUNC | O_RDWR,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (fd_write == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
			cmd->r_out = TRUE;
		}
		if (lst->type == APPEND)
		{
			if (cmd->r_out == TRUE)
				if (close(fd_write) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_write = open(lst->name, O_CREAT | O_APPEND | O_RDWR,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (fd_write == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
			cmd->r_out = TRUE;
		}
		if (lst->type == R_IN)
		{
			if (cmd->r_in == TRUE)
				if (close(fd_read) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_read = open(lst->name, O_RDONLY);
			if (fd_read == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
			cmd->r_in = TRUE;
		}
		if (lst->type == HERE)
		{
			; // WIP
		}
		lst = lst->next;
	}
	if (cmd->r_in)
	{
		if (dup2(fd_read, STDIN_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(fd_read) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	if (cmd->r_out)
	{
		if (dup2(fd_write, STDOUT_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(fd_write) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	ft_env_return(shell, EXIT_SUCCESS);
	return (1);
}
