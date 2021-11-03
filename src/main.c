#include "minishell.h"

static void
	ft_parser_debug(t_shell *shell)
{
	int	i;
	int	cnt;

	cnt = 0;
	while (cnt < shell->cmd_cnt)
	{
		i = 0;
		ft_printf("---CMD %d---\n", cnt);
		while (shell->cmd[cnt].argv && shell->cmd[cnt].argv[i])
		{
			ft_printf("WORD\t%s\n", shell->cmd[cnt].argv[i]);
			i++;
		}
		ft_rdr_iter(shell->cmd[cnt].redir, ft_rdr_print);
		ft_printf("-----------\n", cnt);
		cnt++;
	}
}

int
	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line_read;

	(void)argc;
	(void)argv;
	ft_env_init(&shell, envp);
	line_read = NULL;
	ft_signal();
	ft_header();
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
			break; // DEBUG
		}
		if (line_read && *line_read)
		{
			add_history(line_read);
			if (ft_parser(line_read, &shell))
			{
				ft_parser_debug(&shell);
				signal(SIGINT, SIG_IGN);
				ft_exec(&shell);
				ft_gc_cmd(&shell);
				signal(SIGINT, ft_sig_int);
			}
		}
	}
	ft_gc(&shell);
	return (EXIT_SUCCESS);
}
