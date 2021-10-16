#include "minishell.h"

void
	ft_cmd_asm(t_token *tkn, t_shell *shell) // WIP
{
	int	i;
	int	j;

	shell->cmd = ft_calloc(2, sizeof(*shell->cmd));
	shell->cmd[0] = ft_calloc(ft_argc(tkn->token) + 1, sizeof(**shell->cmd));
	i = 0;
	j = 0;
	while (tkn->token[j])
	{
		shell->cmd[i][j] = tkn->token[j];
		// shell->cmd[i][j] = ft_strdup(tkn->token[j]);
		j++;
	}
	free (tkn->token);
	free (tkn->tkn_literal);
}
