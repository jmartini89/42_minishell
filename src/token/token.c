#include "minishell.h"

int	ft_token(char *line, t_shell *shell)
{
	t_token	tkn;
	int		i;

	if (!ft_syntax(line))
		return (0);
	shell->token = NULL;
	ft_token_init_all(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_find(&tkn, &line[i]);
		if (tkn.end)
		{
			ft_token_assembler(&tkn, shell);
			ft_token_init_all(&tkn);
		}
	}
	return (1);
}
