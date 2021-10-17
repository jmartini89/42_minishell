#include "minishell.h"

int
	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line_read;

	ft_env_init(&shell, envp);
	line_read = NULL;
	ft_signal();
	ft_printf("%d\n", getpid()); // DEBUG
	while (1)
	{
		if (line_read)
		{
			free (line_read);
			line_read = NULL;
		}
		line_read = readline(M_SHELL_PROMPT);
		if (line_read == NULL)
		{
			free (line_read);
			line_read = NULL;
			//ft_exit(&shell, NULL);
			ft_printf("exit\n"); // DEBUG
			break ; // DEBUG
		}
		if (line_read && *line_read)
		{
			add_history(line_read);
			if (ft_token(line_read, &shell))
			{
				signal(SIGINT, SIG_IGN);
				ft_builtin_check(&shell, shell.cmd[0]);
				ft_gc_cmd(shell.cmd, shell.cmd_operator);
				signal(SIGINT, ft_sig_int);
			}
		}
	}
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
