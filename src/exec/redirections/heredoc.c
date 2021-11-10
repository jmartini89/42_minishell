#include "minishell.h"

static void
	ft_wait_heredoc(t_shell *shell, pid_t pid)
{
	int	wstatus;
	int	wexit;

	wexit = waitpid(pid, &wstatus, WUNTRACED);
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
}

static void
	ft_heredoc_child(t_redir *lst)
{
	char	*line;
	int		fd;
	size_t	len;

	rl_catch_signals = 1;
	signal(SIGINT, SIG_DFL);
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
		{
			ft_error(WRN_HEREDOC, NULL);
			if (close(fd) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
			exit (EXIT_FAILURE);
		}
		if (line && *line)
		{
			if (ft_strlen(line) == len && !ft_memcmp(lst->name, line, len))
			{
				free (line);
				if (close(fd) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
				exit (EXIT_SUCCESS);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free (line);
		}
	}
}

static int
	ft_heredoc_fork(t_shell *shell, t_redir *lst)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error_exit(errno, "fork", EXIT_FAILURE);
	if (pid == 0)
		ft_heredoc_child(lst);
	else
		ft_wait_heredoc(shell, pid);
	ft_printf("HEREDOC RET %s\n", shell->ret_str);
	if (ft_atoi(shell->ret_str) > 0)
		return (0);
	return (1);
}

int
	ft_heredoc(t_shell *shell, t_redir *lst)
{
	if (lst == NULL)
		return (1);
	while (lst)
	{
		if (lst->type == HERE)
			if (!ft_heredoc_fork(shell, lst))
				return (0);
		lst = lst->next;
	}
	return (1);
}
