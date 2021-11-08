/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:04 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:05 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ft_lexer_validity(t_token *tkn)
{
	int	i;

	i = 0;
	while (tkn->token[i])
	{
		if (tkn->lexer[i] >= PIPE)
		{
			if (tkn->lexer[i] == PIPE && i == 0)
				return (0);
			if (tkn->token[i + 1] == NULL)
				return (0);
			if (tkn->token[i + 1]
				&& tkn->lexer[i + 1] == PIPE)
				return (0);
		}
		i++;
	}
	return (1);
}

int
	ft_lexer_syntax(t_token *tkn, t_shell *shell)
{
	if (!ft_lexer_validity(tkn))
	{
		ft_error(ERR_SYNTAX_TKN, NULL);
		ft_env_return(shell, 2);
		return (0);
	}
	return (1);
}
