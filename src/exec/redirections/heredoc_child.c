/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_child.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:26:14 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/10 18:26:15 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_heredoc_eot(char *name, int fd, size_t len, char *line)
{
	if (ft_strlen(line) == len && !ft_memcmp(name, line, len))
	{
		free (line);
		if (close(fd) == -1)
			ft_error_exit(errno, "close", EXIT_FAILURE);
		exit (EXIT_SUCCESS);
	}
}

static void
	ft_heredoc_prompt(char *name, int fd, size_t len)
{
	char	*line;

	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (line == NULL)
		{
			ft_error(WRN_HEREDOC, NULL);
			if (close(fd) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
			exit (EXIT_FAILURE);
		}
		if (line && *line)
		{
			ft_heredoc_eot(name, fd, len, line);
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free (line);
		}
	}
}

void
	ft_heredoc_child(t_redir *lst)
{
	int		fd;
	size_t	len;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
	fd = open(TMPFILE, O_CREAT | O_TRUNC | O_APPEND | O_RDWR,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
		ft_error_exit(errno, "open", EXIT_FAILURE);
	len = ft_strlen(lst->name);
	ft_heredoc_prompt(lst->name, fd, len);
}
