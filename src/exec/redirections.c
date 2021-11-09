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
	if (fd_read >= 0)
	{
		if (close(fd_read) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	if (fd_write >= 0)
	{
		if (close(fd_write) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	ft_env_return(shell, EXIT_FAILURE);
	return (0);
}

static int
	ft_heredoc(t_redir *lst) // TODO : COMPLETE REWRITE, DIFFERENT LAUNCH LOGIC - good starting point tho
{
	char	*line;
	int		fd;
	int		len;

	fd = open(TMPFILE, O_CREAT |  O_TRUNC | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		ft_error(errno, "open");
		return (0);
	}
	len = ft_strlen(lst->name);
	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (line == NULL)
		{
			ft_error(WRN_HEREDOC, NULL);
			if (close(fd) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
			return (0);
		}
		if (line && *line)
		{
			if (ft_strlen(line) == len && !ft_memcmp(lst->name, line, len))
			{
				free (line);
				if (close(fd) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
				return (1);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free (line);
		}
	}
}

int
	ft_redir(t_shell *shell, t_cmd *cmd)
{
	int		fd_read;
	int		fd_write;
	t_redir	*lst;

	fd_read = -1;
	fd_write = -1;
	lst = cmd->redir;
	if (lst == NULL)
		return (1);
	while (lst)
	{
		if (lst->type == R_IN)
		{
			if (fd_read >= 0)
				if (close(fd_read) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_read = open(lst->name, O_RDONLY);
			if (fd_read == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
		}
		if (lst->type == HERE)
		{
			if (fd_read >= 0)
				if (close(fd_read) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_read = open(TMPFILE, O_RDONLY);
			if (fd_read == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
		}
		if (lst->type == R_OUT)
		{
			if (fd_write >= 0)
				if (close(fd_write) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_write = open(lst->name, O_CREAT | O_TRUNC | O_RDWR,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (fd_write == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
		}
		if (lst->type == APPEND)
		{
			if (fd_write >= 0)
				if (close(fd_write) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			fd_write = open(lst->name, O_CREAT | O_APPEND | O_RDWR,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (fd_write == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, fd_write, fd_read));
			}
		}
		lst = lst->next;
	}
	if (fd_read)
	{
		if (dup2(fd_read, STDIN_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(fd_read) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	if (fd_write)
	{
		if (dup2(fd_write, STDOUT_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(fd_write) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	ft_env_return(shell, EXIT_SUCCESS);
	return (1);
}
