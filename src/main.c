#include "minishell.h"


int	ft_env_init(char **envp)
{
	int		env_len;
	int		i;

	env_len = 0;
	while (envp[env_len])
		env_len++;
	i = -1;
	while (++i < env_len)
	{
		envp[i] = ft_strdup(envp[i]);
		if (!envp[i])
			return (ft_perror(ERR_SYS_MALLOC));
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line_read;
	char	**exec_arg;
	int		tkn_status;
	int		wstatus;
	int		err;

	shell.env = envp;
	line_read = NULL;
	exec_arg = NULL;

	if (ft_env_init(shell.env) < 0)
		return (EXIT_FAILURE);
	ft_signal();
	while (1)
	{
		g_pid = getpid();
		ft_printf("%d\n", g_pid);
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
				g_pid = fork(); // WTF???
				if (!g_pid)
				{
					if (execve(line_read, exec_arg, shell.env) < 0)
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
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
