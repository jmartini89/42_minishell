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

static int
	ft_redir_fail(t_shell *shell, t_cmd *cmd, int *io)
{
	if (io[0] >= 0)
	{
		if (close(io[0]) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	if (io[1] >= 0)
	{
		if (close(io[1]) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	ft_env_return(shell, EXIT_FAILURE);
	return (0);
}

int
	ft_redir(t_shell *shell, t_cmd *cmd)
{
	int		io[2];
	t_redir	*lst;

	io[0] = -1;
	io[1] = -1;
	lst = cmd->redir;
	if (lst == NULL)
		return (1);
	while (lst)
	{
		if (lst->type == R_IN || lst->type == HERE)
		{
			if (io[0] >= 0)
				if (close(io[0]) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			if (lst->type == R_IN)
				io[0] = open(lst->name, O_RDONLY);
			if (lst->type == HERE)
				io[0] = open(TMPFILE, O_RDONLY);
			if (io[0] == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, io));
			}
		}
		if (lst->type == R_OUT || lst->type == APPEND)
		{
			if (io[1] >= 0)
				if (close(io[1]) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
			if (lst->type == R_OUT)
				io[1] = open(lst->name, O_CREAT | O_TRUNC | O_RDWR,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (lst->type == APPEND)
				io[1] = open(lst->name, O_CREAT | O_APPEND | O_RDWR,
						S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
			if (io[1] == -1)
			{
				ft_error(errno, "open");
				return (ft_redir_fail(shell, cmd, io));
			}
		}
		lst = lst->next;
	}
	if (io[0] >= 0)
	{
		if (dup2(io[0], STDIN_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(io[0]) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	if (io[1] >= 0)
	{
		if (dup2(io[1], STDOUT_FILENO) == -1)
			ft_error_exit(errno, "dup2", EXIT_FAILURE);
		if (close(io[1]) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
	}
	ft_env_return(shell, EXIT_SUCCESS);
	return (1);
}
