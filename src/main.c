#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line_read;
	int		pid;
	int		wstatus;
	int		wexit;
	int		err;

	ft_env_init(&shell, envp);
	line_read = NULL;
	while (1)
	{
		ft_signal();
		if (line_read)
		{
			free (line_read);
			line_read = NULL;
		}

		line_read = readline("\e[32m"M_SHELL_NAME"\e[0m$ ");

		if (line_read == NULL) // TODO : EXIT COMMAND & EXIT STATUS
		{
			ft_printf("exit\n");
			free (line_read);
			line_read = NULL;
			break;
		}

		if (line_read && *line_read)
		{
			add_history(line_read); // TODO : avoid repetitions
			if (ft_token(line_read, &shell))
			{
				if (!ft_builtin(&shell, shell.token))
				{
					pid = fork();
					if (pid < 0)
						ft_perror_exit(ERR_SYS_FORK);
					if (!pid)
					{
						if (execve(shell.token[0], shell.token, shell.env) < 0)
						{
							err = errno;
							free (line_read);
							line_read = NULL;
							ft_perror_exit(ERR_EXEC_NOFILE);
							if (err == ENOENT)
								exit (127);
							if (err == EPERM)
								exit (126);
							else // TODO : PROPER EXIT
								exit (err);
						}
					}
					else
					{
						signal(SIGINT, ft_sig_void);
						wexit = wait(&wstatus);
						if (wexit < 0)
							ft_perror_exit(ERR_SYS_FORK);
						if (WIFSIGNALED(wstatus))
						{
							ft_printf("\n");
							ft_env_return(&shell, WTERMSIG(wstatus) + 128);
							ft_printf("EXIT STATUS\t%s\n", shell.ret_str);
						}
						if (WEXITSTATUS(wstatus))
						{
							ft_env_return(&shell, WEXITSTATUS(wstatus));
							ft_printf("EXIT STATUS\t%s\n", shell.ret_str);
						}
					}
				}
				ft_gc_token(shell.token, shell.tkn_literal);
			}
		}
	}
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
