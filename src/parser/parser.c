#include "minishell.h"

static void
	ft_parser_null_heap(t_token *tkn)
{
	tkn->token = NULL;
	tkn->tkn_literal = NULL;
	tkn->lexer = NULL;
}

static void
	ft_parser_gc(t_token *tkn)
{
	ft_gc_2p_str(tkn->token);
	free (tkn->tkn_literal);
	free (tkn->lexer);
}

int
	ft_parser(char *line, t_shell *shell)
{
	t_token	tkn;

	ft_parser_null_heap(&tkn);
	if (ft_token(line, &tkn, shell) == 0
		|| ft_lexer(&tkn, shell) == 0)
	{
		ft_parser_gc(&tkn);
		return (0);
	}
	ft_cmd_asm(&tkn, shell);
	ft_parser_gc(&tkn);
	return (1);
}
