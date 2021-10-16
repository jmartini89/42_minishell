#include "minishell.h"

void
	ft_cmd_asm(t_token *tkn, t_shell *shell) // WIP
{
	int	i;

	shell->cmd = ft_calloc(2, sizeof(*shell->cmd));
	shell->cmd[0] = ft_calloc(ft_argc(tkn->token) + 1, sizeof(**shell->cmd));
	i = -1;
	while (tkn->token[++i])
	{
		shell->cmd[0][i] = ft_strdup(tkn->token[i]);
		if (!shell->cmd[0][i])
			ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	}
}
