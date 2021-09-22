#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line_read;
	char	**exec_arg;
	int		tkn_status;
	int		pid;
	int		wstatus;
	int		wexit;
	int		err;

	line_read = NULL;
	exec_arg = NULL;

	if (!ft_env_init(&shell, envp))
		return (EXIT_FAILURE);

/*
** CWD TEST
	shell.cwd = getcwd(NULL, 0);
	ft_printf("%s\n", shell.cwd);
	chdir("..");
	free (shell.cwd);
	shell.cwd = getcwd(NULL, 0);
	ft_printf("%s\n", shell.cwd);
	free (shell.cwd);
*/

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
			tkn_status = ft_token(line_read, &shell);
			if (tkn_status > 0)
			{
				pid = fork();
				if (pid < 0)
				{
					ft_perror(ERR_SYS_FORK);
					return (EXIT_FAILURE);
				}
				if (!pid)
				{
					if (execve(line_read, exec_arg, shell.env) < 0)
					{
						err = errno;
						ft_perror(ERR_EXEC_NOFILE);
						free (line_read);
						line_read = NULL;
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
					{
						ft_perror(ERR_SYS_FORK);
						return (EXIT_FAILURE);
					}
					if (WIFSIGNALED(wstatus))
					{
						ft_printf("\n");
						ft_printf("EXIT STATUS\t%d\n", WTERMSIG(wstatus) + 128);
					}
					if (WEXITSTATUS(wstatus))
						ft_printf("EXIT STATUS\t%d\n", WEXITSTATUS(wstatus));
				}
			}
			else if (tkn_status < 0)
				return (EXIT_FAILURE);
		}
	}
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
