#include "minishell.h"

static void
	ft_lexer_tag(t_token *tkn)
{
	int	i;
	int	len;

	len = ft_argc(tkn->token);
	tkn->lexer = ft_calloc(len, sizeof(*tkn->lexer));
	if (tkn->lexer == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	i = 0;
	while (tkn->token[i])
	{
		if (tkn->tkn_literal[i])
			tkn->lexer[i] = WORD;
		else
			tkn->lexer[i] = ft_operator_type(tkn->token[i]);
		ft_printf("LEXER\t%s\t%d\n", tkn->token[i], tkn->lexer[i]);
		i++;
	}
}

int
	ft_lexer(t_token *tkn, t_shell *shell)
{
	tkn->lexer = NULL;
	ft_lexer_tag(tkn);
	if (ft_lexer_syntax(tkn, shell) == 0) // TODO
		return (0);
	return (1);
}
