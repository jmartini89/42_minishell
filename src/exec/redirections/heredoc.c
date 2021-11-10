#include "minishell.h"

static void
	ft_heredoc_child(t_redir *lst)
{
	char	*line;
	int		fd;
	size_t	len;

	signal(SIGINT, ft_sig_int);
	fd = open(TMPFILE, O_CREAT |  O_TRUNC | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
		ft_error_exit(errno, "open", EXIT_FAILURE);
	len = ft_strlen(lst->name);
	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (line == NULL)
			break ;
		if (line && *line)
		{
			if (ft_strlen(line) == len && !ft_memcmp(lst->name, line, len))
			{
				free (line);
				if (close(fd) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
				exit (1);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free (line);
		}
	}
	ft_error(WRN_HEREDOC, NULL);
	if (close(fd) == -1)
		ft_error_exit(errno, "close", EXIT_FAILURE);
	exit (1);
}

static void
	ft_heredoc_fork(t_shell *shell, t_redir *lst)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_exit(errno, "fork", EXIT_FAILURE);
	if (pid == 0)
		ft_heredoc_child(lst);
	else
		ft_wait_one(shell, pid);
}

int
	ft_heredoc(t_shell *shell, t_redir *lst)
{
	if (lst == NULL)
		return (1);
	while (lst)
	{
		if (lst->type == HERE)
			ft_heredoc_fork(shell, lst);
		lst = lst->next;
	}
	return (1);
}
