#include "minishell.h"

int
	ft_parser(char *line, t_shell *shell)
{
	t_token	tkn;

	if (ft_lexer(line, &tkn, shell))
	{
		ft_cmd_asm(&tkn, shell);
		return (1);
	}
	return (0);
}
