#include "minishell.h"

int
	ft_lexer(t_token *tkn, t_shell *shell)
{
	if (ft_lexer_syntax(tkn, shell) == 0)
		return (0);
	return (1);
}
