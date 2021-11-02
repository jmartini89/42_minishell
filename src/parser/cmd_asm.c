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

	i = 0;
	cnt = 0;
	while (tkn->token[i])
	{
		if (tkn->token[i] && tkn->lexer[i] == WORD)
		{
			cnt++;
			while (tkn->token[i] && tkn->lexer == WORD)
				i++;
		}
		if (tkn->token[i] && tkn->lexer[i] == PIPE)
			cnt++;
		if (tkn->token[i] && tkn->lexer[i] > PIPE) // NOT OK FOR EDGE CASE, NEED DIFFERENT LOGIC
		{
			cnt++;
			i++;
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

	printf("---\nCMD CNT\t%d\n", cmd_cnt);
}
