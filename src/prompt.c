/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:49:43 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/10 18:50:25 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_engine(t_shell *shell, char *line)
{
	ft_history(line);
	if (ft_parser(line, shell))
	{
		signal(SIGINT, SIG_IGN);
		ft_exec(shell);
		ft_gc_cmd(shell);
		signal(SIGINT, ft_sig_int);
	}
}

void
	ft_prompt(t_shell *shell)
{
	char	*line;

	line = NULL;
	while (1)
	{
		if (line)
		{
			free (line);
			line = NULL;
		}
		line = readline(M_SHELL_PROMPT);
		if (line == NULL)
		{
			free (line);
			line = NULL;
			ft_exit(shell, NULL, FALSE);
		}
		if (line && *line)
			ft_engine(shell, line);
	}
}
