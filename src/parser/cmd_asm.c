#include "minishell.h"

static void
	ft_cmd_init(t_shell *shell)
{
	shell->cmd = NULL;
	shell->cmd_operator = NULL;
	shell->cmd_cnt = 0;
}

int
	ft_cmd_cnt(t_token *tkn) // NOT WORKING PROPERLY
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 1;
	while (tkn->token[i])
	{
		if (tkn->lexer[i] == PIPE)
		{
			cnt++;
			if (tkn->token[i + 1]
				&& tkn->lexer[i + 1] == WORD)
				cnt++;
		}
		if (tkn->lexer[i] > PIPE)
		{
			cnt++;
			while (tkn->token[i + 1] && tkn->token[i + 2]
				&& tkn->lexer[i + 2] > PIPE)
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

	printf("CMD CNT\t%d\n", cmd_cnt);
}
