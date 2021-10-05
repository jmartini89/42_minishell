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
			ft_exit(&shell, NULL);
		}

		if (line_read && *line_read)
		{
			add_history(line_read); // TODO : avoid repetitions
			if (ft_token(line_read, &shell))
			{
				ft_builtin(&shell, shell.token);
				ft_gc_token(shell.token, shell.tkn_literal);
			}
		}
	}
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
