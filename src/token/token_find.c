#include "minishell.h"

int	ft_token_quotes_status(t_token *tkn, char c)
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

/* TODO : OPERATOR PROPER IMPLEMENTATION */
static void	ft_token_start_end(t_token *tkn, char *c)
{
	if (ft_is_operator(*c) && !tkn->start)
	{
		tkn->start = c;
		tkn->end = c;
	}
	if (!ft_is_space_tab(*c) && !tkn->start)
		tkn->start = c;
	if (ft_is_operator(*(c + 1))
		&& tkn->start && !tkn->end && tkn->quotes_status == QTS_CLOSE)
		tkn->end = c;
	if (ft_is_space_tab(*c)
		&& tkn->start && !tkn->end && tkn->quotes_status == QTS_CLOSE)
		tkn->end = c - 1;
	if (*(c + 1) == '\0' && !ft_is_space_tab(*c))
		tkn->end = c;
}

void	ft_token_find(t_token *tkn, char *c)
{
	ft_token_quotes_status(tkn, *c);
	ft_token_start_end(tkn, c);
}
