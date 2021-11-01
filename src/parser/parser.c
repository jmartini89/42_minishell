#include "minishell.h"

int
	ft_parser(char *line, t_shell *shell)
{
	t_token	tkn;

	if (ft_token(line, &tkn, shell) == 0
		|| ft_lexer(&tkn, shell) == 0)
		return (0);
	ft_cmd_asm(&tkn, shell);
	return (1);
}
