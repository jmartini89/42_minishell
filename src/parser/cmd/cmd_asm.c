/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:55 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:56 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ft_cmd_word(t_token *tkn, t_list **word, int i)
{
	t_list	*tmp;

	tmp = NULL;
	if (tkn->token[i] && tkn->lexer[i] == WORD)
	{
		tmp = ft_lstnew(tkn->token[i]);
		if (tmp == NULL)
			ft_error_exit(errno, "malloc", EXIT_FAILURE);
		if (*word == NULL)
			*word = tmp;
		else
			ft_lstadd_back(word, tmp);
		return (1);
	}
	return (0);
}

static int
	ft_cmd_redir(t_token *tkn, t_redir **redir, int i)
{
	t_redir	*tmp;

	tmp = NULL;
	if (tkn->token[i] && tkn->lexer[i] > PIPE)
	{
		tmp = ft_rdr_new(tkn->lexer[i], tkn->token[i + 1]);
		if (*redir == NULL)
			*redir = tmp;
		else
			ft_rdr_add_back(redir, tmp);
		free (tkn->token[i]);
		tkn->token[i] = NULL;
		return (1);
	}
	return (0);
}

static void
	ft_cmd_write_word(t_shell *shell, t_list **word, int cnt)
{
	int	lstsize;

	shell->cmd[cnt].argv = NULL;
	lstsize = ft_lstsize(*word);
	if (lstsize)
	{
		shell->cmd[cnt].argv = ft_calloc(
				lstsize + 1, sizeof(*shell->cmd[cnt].argv));
		if (shell->cmd[cnt].argv == NULL)
			ft_error_exit(errno, "malloc", EXIT_FAILURE);
	}
	ft_word_cpy(shell, *word, cnt);
	ft_lstclear(word, NULL);
}

static int
	ft_cmd_pipe(t_token *tkn, int i)
{
	if (tkn->token[i] && tkn->lexer[i] == PIPE)
	{
		free (tkn->token[i]);
		tkn->token[i] = NULL;
		return (1);
	}
	return (0);
}

void
	ft_cmd_asm(t_token *tkn, t_shell *shell, t_list *word, t_redir *redir)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (tkn->token[i])
	{
		if (ft_cmd_word(tkn, &word, i))
			i++;
		if (ft_cmd_redir(tkn, &redir, i))
			i += 2;
		if ((tkn->token[i] && tkn->lexer[i] == PIPE)
			|| tkn->token[i] == NULL)
		{
			if (ft_cmd_pipe(tkn, i))
				i++;
			ft_cmd_write_word(shell, &word, cnt);
			shell->cmd[cnt].redir = redir;
			redir = NULL;
			cnt++;
		}
	}
}
