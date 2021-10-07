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
	ft_signal();
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
				signal(SIGINT, SIG_IGN); // TEST PURPOSE, MAYBE NOT A GOOD IDEA
				ft_builtin(&shell, shell.token);
				ft_gc_token(shell.token, shell.tkn_literal);
				signal(SIGINT, ft_sig_int);
			}
		}
	}
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
