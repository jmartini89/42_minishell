#include "minishell.h"

static int
	ft_token_validity(t_token *tkn)
{
	int	i;
	int	type;

	i = 0;
	while (tkn->token[i])
	{
		type = ft_operator_type(tkn->token[i]);
		if (type >= PIPE && tkn->tkn_literal[i] == 0)
		{
			if (type == PIPE && i == 0)
				return (0);
			if (!tkn->token[i + 1])
				return (0);
			if (tkn->token[i + 1]
				&& ft_operator_type(tkn->token[i + 1]) == PIPE)
				return (0);
		}
		i++;
	}
	return (1);
}

int
	ft_lexer_syntax(t_token *tkn, t_shell *shell)
{
	if (!ft_token_validity(tkn))
	{
		ft_gc_2p_str(tkn->token);
		free (tkn->tkn_literal);
		ft_error(ERR_SYNTAX_TKN, NULL);
		ft_env_return(shell, 2);
		return (0);
	}
	return (1);
}
