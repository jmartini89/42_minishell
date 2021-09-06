#include "minishell.h"

pid_t	g_pid;

void	ft_sig_int(int sig)
{
	ft_printf("^C\n");//BUG IF FORKED
	rl_on_new_line();
	rl_replace_line("", 0);
	//ft_printf("DEBUG %d\n", g_pid);
	if (getpid() == g_pid)
		rl_redisplay();
}

void	ft_sig_quit(int sig)
{
}

int	main(void)
{
	char	*line_read;
	char	**exec_arg;
	int		wstatus;
	int		err;

	line_read = NULL;
	exec_arg = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_quit);

	char	**split_test;
	while (1)
	{
		g_pid = getpid();
		//ft_printf("%d\n", g_pid);
		if (line_read)
		{
			free (line_read);
			line_read = NULL;
		}

		line_read = readline("\e[32mminishell$ \e[0m");

		if (line_read == NULL ||
			(ft_strlen(line_read) == 4 && !ft_memcmp(line_read, "exit", 4)))
		{
			ft_printf("exit\n");
			free (line_read);
			line_read = NULL;
			break;
		}

		if (line_read && *line_read)
		{
			add_history(line_read); // BUG : same command
			if (ft_parser(line_read))
			{
				ft_printf("DEBUG ECHO : %s\n", line_read);
				g_pid = fork();
				if (!g_pid)
				{
					if (execve(line_read, exec_arg, NULL) < 0)
					{
						err = errno;
						ft_printf("%s\n", (strerror(err)));
						free (line_read);
						exit(err);
					}
				}
				else
				{
					while (waitpid(-1, &wstatus, 0) > 0)
						usleep (10);
				}
			}
		}
	}
	return (1);
}
