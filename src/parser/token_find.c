#include "minishell.h"

static void	ft_token_init(t_token *tkn)
{
	tkn->start = NULL;
	tkn->end = NULL;
	tkn->single_quotes = 1;
	tkn->double_quotes = 1;
	tkn->quotes_status = 1;
}

/* TODO : IMPLEMENT ADDRESS SAVE */
static void	ft_token_quotes(t_token *tkn, char *c)
{
	if (*c == '\"' && tkn->single_quotes == 1)
		tkn->double_quotes *= -1;
	if (*c == '\'' && tkn->double_quotes == 1)
		tkn->single_quotes *= -1;
	if (tkn->single_quotes == -1 || tkn->double_quotes == -1)
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
