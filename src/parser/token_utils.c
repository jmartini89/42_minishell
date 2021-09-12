#include "minishell.h"

void	ft_token_init_all(t_token *tkn)
{
	ft_token_init_addr(tkn);
	ft_token_init_quotes(tkn);
}

void	ft_token_init_addr(t_token *tkn)
{
	tkn->start = NULL;
	tkn->end = NULL;
}

void	ft_token_init_quotes(t_token *tkn)
{
	tkn->s_qts = QTS_CLOSE;
	tkn->d_qts = QTS_CLOSE;
	tkn->quotes_status = QTS_CLOSE;
}

int	ft_token_quotes(t_token *tkn, char c)
{
	int	quote;

	quote = ft_is_quote(c);
	if (quote)
	{
		if (quote == QTS_SINGLE && tkn->d_qts == QTS_CLOSE)
			tkn->s_qts *= -1;
		if (quote == QTS_DOUBLE && tkn->s_qts == QTS_CLOSE)
			tkn->d_qts *= -1;
		if (tkn->s_qts == QTS_OPEN || tkn->d_qts == QTS_OPEN)
			tkn->quotes_status = QTS_OPEN;
		else
			tkn->quotes_status = QTS_CLOSE;
	}
}
