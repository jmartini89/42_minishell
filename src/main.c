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

int	main(int argc, char **argv, char **envp)
{
	char	*line_read;
	char	**exec_arg;
	int		tkn_status;
	int		wstatus;
	int		err;

	line_read = NULL;
	exec_arg = NULL;
	rl_catch_signals = 0;
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_quit);

/* ENV TESTS */
	char *test1 = ft_calloc(16, sizeof(*test1));
	char *test2 = ft_calloc(9, sizeof(*test2));
	ft_memcpy(test1, "SHELL="M_SHELL_NAME, ft_strlen("SHELL="M_SHELL_NAME));
	ft_memcpy(test2, "SHLVL=69", ft_strlen("SHLVL=69"));
	int env_len = -1;
	while (envp[++env_len])
		;
	int *heap_env = ft_calloc(env_len, sizeof(*heap_env));
	int i = -1;
	while (envp[++i])
	{
		if (!ft_memcmp(envp[i], "SHELL", 5))
		{
			ft_printf("%d\n", i);
			envp[i] = test1;
			heap_env[i] = 1;
		}
		if (!ft_memcmp(envp[i], "SHLVL", 5))
		{
			ft_printf("%d\n", i);
			envp[i] = test2;
			heap_env[i] = 1;
		}
	}

	while (1)
	{
		g_pid = getpid();
		//ft_printf("%d\n", g_pid);
		if (line_read)
		{
			free (line_read);
			line_read = NULL;
		}

		line_read = readline("\e[32m"M_SHELL_NAME"\e[0m$ ");

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
			add_history(line_read); // BUG : line repetition
			tkn_status = ft_token(line_read);
			if (tkn_status > 0)
			{
				g_pid = fork();
				if (!g_pid)
				{
					if (execve(line_read, exec_arg, envp) < 0)
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
			else if (tkn_status < 0)
				return (EXIT_FAILURE);
		}
	}
	
/* ENV FREE */
	i = -1;
	while (++i < env_len)
	{
		if (heap_env[i])
		{
			ft_printf("%d\n", i);
			free (envp[i]);
		}
	}
	free (heap_env);
	return (EXIT_SUCCESS);
}
