#include "minishell.h"

static void
	ft_token_literal(t_shell *shell, int len)
{
	int	*tmp;

	tmp = shell->tkn_literal;
	if (tmp)
		ft_memcpy(tmp, shell->tkn_literal, sizeof(*tmp) * len);
	shell->tkn_literal = ft_calloc(len + 1, sizeof(*shell->tkn_literal));
	if (!shell->tkn_literal)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	ft_memcpy(shell->tkn_literal, tmp, sizeof(*tmp) * len);
	free (tmp);
	if (shell->literal)
		shell->tkn_literal[len] = 1;
}

static int
	ft_token_assembler_swap(t_shell *shell)
{
	int		len;
	int		i;
	char	**tmp;

	tmp = shell->token;
	len = 0;
	while (tmp && tmp[len])
	{
		tmp[len] = shell->token[len];
		len++;
	}
	shell->token = ft_calloc(len + 2, sizeof(*shell->token));
	if (!shell->token)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	i = 0;
	while (tmp && tmp[i])
	{
		shell->token[i] = tmp[i];
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
	shell->literal = 0;
	new_tkn = ft_token_translate(tkn, shell);
	if (*new_tkn)
	{
		i = ft_token_assembler_swap(shell);
		shell->token[i] = new_tkn;
		ft_token_literal(shell, i);
		//ft_printf("TOKEN %d : %s\n", shell->tkn_literal[i], shell->token[i]);
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
	shell->token = NULL;
	shell->tkn_literal = NULL;
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
	if (shell->token)
		return (1);
	return (0);
}
