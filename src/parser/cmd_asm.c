#include "minishell.h"

static void
	ft_cmd_init(t_shell *shell)
{
	shell->cmd = NULL;
	shell->cmd_operator = NULL;
	shell->cmd_cnt = 0;
}

int
	ft_cmd_cnt(t_token *tkn)
{
	int	i;
	int	cnt;
	int	type;

	i = 0;
	cnt = 1;
	while (tkn->token[i])
	{
		type = ft_operator_type(tkn->token[i]);
		if (type == PIPE)
		{
			cnt++;
			if (tkn->token[i + 1]
				&& ft_operator_type(tkn->token[i + 1]) == WORD)
				cnt++;
		}
		if (type > PIPE)
		{
			cnt++;
			while (tkn->token[i + 1] && tkn->token[i + 2]
				&& ft_operator_type(tkn->token[i + 2]) > PIPE)
				i += 2;
		}
		i++;
	}
	return (cnt);
}

void
	ft_cmd_asm(t_token *tkn, t_shell *shell)
{
	int	cmd_cnt;

	ft_cmd_init(shell);
	cmd_cnt = ft_cmd_cnt(tkn);

	printf("%d\n", cmd_cnt);

	/* NO LEAK DEBUG */
	ft_gc_2p_str(tkn->token);
	free (tkn->tkn_literal);
}
