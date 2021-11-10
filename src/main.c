/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:55 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 17:13:29 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ft_prompt()
{
	;
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
			/* DEBUG LEAK EXIT */
			return (ft_debug_leaks_at_exit(&shell));
		}
		if (line_read && *line_read)
		{
			add_history(line_read);
			if (ft_parser(line_read, &shell))
			{
				signal(SIGINT, SIG_IGN);
				// ft_debug_parser(&shell);
				ft_exec(&shell);
				ft_gc_cmd(&shell);
				signal(SIGINT, ft_sig_int);
			}
		}
	}
	exit (EXIT_SUCCESS);
}
