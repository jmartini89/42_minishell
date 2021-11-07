/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:23 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:24 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_token_quotes_status(t_token *tkn, char c)
{
	int	quote;
	int	status;

	quote = ft_is_quote(c);
	if (quote)
	{
		status = tkn->s_qts * tkn->d_qts;
		if (quote == QTS_SINGLE && tkn->d_qts == QTS_CLOSE)
			tkn->s_qts *= -1;
		if (quote == QTS_DOUBLE && tkn->s_qts == QTS_CLOSE)
			tkn->d_qts *= -1;
		if (tkn->s_qts == QTS_OPEN || tkn->d_qts == QTS_OPEN)
			tkn->quotes_status = QTS_OPEN;
		else
			tkn->quotes_status = QTS_CLOSE;
		if (status != tkn->s_qts * tkn->d_qts)
			return (1);
		else
			return (0);
	}
	return (0);
}

static void
	ft_token_partition_operator(t_token *tkn, char *c)
{
	int	operator;

	operator = ft_is_operator(*c);
	if (operator == PIPE)
	{
		tkn->start = c;
		tkn->end = c;
	}
	if ((operator == R_IN || operator == R_OUT)
		&& ft_is_operator(*(c + 1)) == operator)
	{
		tkn->start = c;
		tkn->end = c + 1;
	}
	if ((operator == R_IN || operator == R_OUT)
		&& !ft_is_operator(*(c + 1)))
	{
		tkn->start = c;
		tkn->end = c;
	}
}

static void
	ft_token_partition(t_token *tkn, char *c)
{
	if (ft_is_operator(*c) && !tkn->start)
		ft_token_partition_operator(tkn, c);
	if (!ft_is_space_tab(*c) && !tkn->start)
		tkn->start = c;
	if (ft_is_operator(*(c + 1)) && !ft_is_space_tab(*c)
		&& tkn->start && !tkn->end && tkn->quotes_status == QTS_CLOSE)
		tkn->end = c;
	if (ft_is_space_tab(*c)
		&& tkn->start && !tkn->end && tkn->quotes_status == QTS_CLOSE)
		tkn->end = c - 1;
	if (*(c + 1) == '\0' && !ft_is_space_tab(*c))
		tkn->end = c;
}

void
	ft_token_find(t_token *tkn, char *c)
{
	ft_token_quotes_status(tkn, *c);
	ft_token_partition(tkn, c);
}
