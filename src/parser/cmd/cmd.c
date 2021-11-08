/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:57 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:58 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_cmd_cnt(t_token *tkn)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (tkn->token[i])
	{
		if (tkn->lexer[i] == PIPE)
			cnt++;
		i++;
	}
	return (cnt + 1);
}

void
	ft_word_cpy(t_shell *shell, t_list *word, int index)
{
	int	i;

	i = 0;
	while (word)
	{
		shell->cmd[index].argv[i] = word->content;
		word = word->next;
		i++;
	}
}

void
	ft_cmd(t_token *tkn, t_shell *shell)
{
	t_list	*word;
	t_redir	*redir;

	word = NULL;
	redir = NULL;
	shell->cmd_cnt = ft_cmd_cnt(tkn);
	shell->cmd = ft_calloc(shell->cmd_cnt, sizeof(*shell->cmd));
	if (shell->cmd == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	ft_cmd_asm(tkn, shell, word, redir);
}
