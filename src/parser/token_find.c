#include "minishell.h"

static void	ft_token_init(t_token *tkn)
{
	tkn->start = NULL;
	tkn->end = NULL;
	tkn->quotes = NULL;
	tkn->s_qts = QTS_CLOSE;
	tkn->d_qts = QTS_CLOSE;
	tkn->quotes_status = QTS_CLOSE;
}

static void	ft_token_quotes_address(t_token *tkn, char *c, int status)
{
	int		len;
	char	**tmp;

	if (!tkn->quotes)
		tkn->quotes = ft_calloc(1, sizeof(*tkn->quotes));
	tmp = tkn->quotes;
	len = -1;
	while (tkn->quotes[++len])
		tmp[len] = tkn->quotes[len];
	tkn->quotes = ft_calloc(len + 2, sizeof(*tkn->quotes));
	len = -1;
	while (tmp[++len])
		tkn->quotes[len] = tmp[len];
	free (tmp);
	tkn->quotes[len] = c;
	ft_printf("QTS DEBUG FIND\t: %d\t%p\n", len, tkn->quotes[len]);
}

static void	ft_token_quotes(t_token *tkn, char *c)
{
	int	quote;
	int	status;

	status = tkn->s_qts * tkn->d_qts;
	quote = ft_is_quote(*c);
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
		if (status != tkn->s_qts * tkn->d_qts)
			ft_token_quotes_address(tkn, c, tkn->quotes_status);
	}
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
