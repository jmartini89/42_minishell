#include "minishell.h"

int
	ft_parser(char *line, t_shell *shell)
{
	t_token	tkn;

	if (ft_token(line, &tkn, shell) == 0
		|| ft_lexer(&tkn, shell) == 0)
		return (0);
	ft_cmd_asm(&tkn, shell);

	/* NO LEAK DEBUG */
	ft_gc_2p_str(tkn.token);
	free (tkn.tkn_literal);
	free (tkn.lexer);

	return (1);
}
