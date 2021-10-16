#include "minishell.h"

static void
	ft_token_literal(t_token *tkn, int len)
{
	int	*tmp;

	tmp = tkn->tkn_literal;
	if (tmp)
		ft_memcpy(tmp, tkn->tkn_literal, sizeof(*tmp) * len);
	tkn->tkn_literal = ft_calloc(len + 1, sizeof(*tkn->tkn_literal));
	if (!tkn->tkn_literal)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	ft_memcpy(tkn->tkn_literal, tmp, sizeof(*tmp) * len);
	free (tmp);
	if (tkn->literal)
		tkn->tkn_literal[len] = 1;
}

static int
	ft_token_assembler_swap(t_token *tkn)
{
	int		len;
	int		i;
	char	**tmp;

	tmp = tkn->token;
	len = 0;
	while (tmp && tmp[len])
	{
		tmp[len] = tkn->token[len];
		len++;
	}
	tkn->token = ft_calloc(len + 2, sizeof(*tkn->token));
	if (!tkn->token)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	i = 0;
	while (tmp && tmp[i])
	{
		tkn->token[i] = tmp[i];
		i++;
	}
	free (tmp);
	return (len);
}

static void
	ft_token_assembler(t_token *tkn, t_shell *shell)
{
	int		i;
	char	*new_tkn;

	ft_token_init_quotes(tkn);
	tkn->literal = 0;
	new_tkn = ft_token_translate(tkn, shell);
	if (*new_tkn)
	{
		i = ft_token_assembler_swap(tkn);
		tkn->token[i] = new_tkn;
		ft_token_literal(tkn, i);
	}
	else
		free (new_tkn);
}

int
	ft_token(char *line, t_shell *shell)
{
	t_token	tkn;

	if (!ft_syntax(line, shell))
		return (0);
	tkn.token = NULL;
	tkn.tkn_literal = NULL;
	ft_token_init_all(&tkn);
	while (*line)
	{
		ft_token_find(&tkn, line);
		if (tkn.end)
		{
			line = tkn.end;
			ft_token_assembler(&tkn, shell);
			ft_token_init_all(&tkn);
		}
		line++;
	}
	if (tkn.token)
	{
		ft_cmd_asm(&tkn, shell);
		ft_gc_token(tkn.token, tkn.tkn_literal);
		return (1);
	}
	return (0);
}
