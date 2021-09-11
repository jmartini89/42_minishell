#include "minishell.h"

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

	ft_token_init_all(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_quotes(&tkn, &line[i]);
		ft_token_start_end(&tkn, &line[i]);
		if (tkn.end)
		{
			ft_token_assembler(&tkn);
			ft_token_init_all(&tkn);
		}
	}
}
