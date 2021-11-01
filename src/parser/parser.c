#include "minishell.h"

static int
	ft_tokenizer(char *line, t_token *tkn, t_shell *shell)
{
	if (!ft_token_syntax(line, shell))
		return (0);
	tkn->token = NULL;
	tkn->tkn_literal = NULL;
	ft_token_init_all(tkn);
	while (*line)
	{
		ft_token_find(tkn, line);
		if (tkn->end)
		{
			line = tkn->end;
			ft_lexer(tkn, shell);
			ft_token_init_all(tkn);
		}
		line++;
	}
}

int
	ft_parser(char *line, t_shell *shell)
{
	t_token	tkn;

	if (ft_tokenizer(line, &tkn, shell))
		return (0);
	if (tkn.token)
	{
		if (!ft_lexer_syntax(&tkn, shell))
			return (0);
		ft_cmd_asm(&tkn, shell);
		return (1);
	}
	return (0);
}
