/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:34 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:35 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_parser_null_heap(t_token *tkn)
{
	tkn->token = NULL;
	tkn->tkn_literal = NULL;
	tkn->lexer = NULL;
}

static void
	ft_parser_gc(t_token *tkn, int exit)
{
	if (exit)
		ft_gc_2p_str(tkn->token);
	else
		free (tkn->token);
	free (tkn->tkn_literal);
	free (tkn->lexer);
}

int
	ft_parser(char *line, t_shell *shell)
{
	t_token	tkn;

	ft_parser_null_heap(&tkn);
	if (ft_token(line, &tkn, shell) == 0)
		return (0);
	if (ft_lexer(&tkn, shell) == 0)
	{
		ft_parser_gc(&tkn, TRUE);
		return (0);
	}
	ft_cmd(&tkn, shell);
	ft_parser_gc(&tkn, FALSE);
	return (1);
}
