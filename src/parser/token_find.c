#include "minishell.h"

static void	ft_token_init(t_token *tkn)
{
	tkn->start = NULL;
	tkn->end = NULL;
	tkn->quotes = NULL;
	tkn->s_qts = 1;
	tkn->d_qts = 1;
	tkn->quotes_status = 1;
}

static void	ft_token_quotes_address(t_token *tkn, int status)
{
	if (status == QTS_ADDR_START)
		;
}

static void	ft_token_quotes(t_token *tkn, char *c)
{
	if (ft_is_quote(*c) == QTS_SINGLE && tkn->d_qts == 1)
	{
		tkn->s_qts *= -1;
		if (tkn->s_qts == -1)
			ft_token_quotes_address(tkn, QTS_ADDR_START);
		else
			ft_token_quotes_address(tkn, QTS_ADDR_END);
	}
	if (ft_is_quote(*c) == QTS_DOUBLE && tkn->s_qts == 1)
	{
		tkn->d_qts *= -1;
		if (tkn->d_qts == -1)
			ft_token_quotes_address(tkn, QTS_ADDR_START);
		else
			ft_token_quotes_address(tkn, QTS_ADDR_END);
	}
	if (tkn->s_qts == -1 || tkn->d_qts == -1)
		tkn->quotes_status = -1;
	else
		tkn->quotes_status = 1;
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
		&& tkn->start && !tkn->end && tkn->quotes_status == 1)
		tkn->end = c;
	if (ft_is_space_tab(*c)
		&& tkn->start && !tkn->end && tkn->quotes_status == 1)
		tkn->end = c - 1;
	if (*(c + 1) == '\0' && !ft_is_space_tab(*c))
		tkn->end = c;
}

void	ft_token(char *line)
{
	t_token	tkn;
	int		i;

	ft_token_init(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_quotes(&tkn, &line[i]);
		ft_token_start_end(&tkn, &line[i]);
		if (tkn.end)
		{
			ft_token_assembler(&tkn);
			ft_token_init(&tkn);
		}
	}
}
