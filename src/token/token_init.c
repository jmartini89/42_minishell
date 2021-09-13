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
