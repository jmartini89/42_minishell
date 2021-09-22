#include "minishell.h"

int	ft_token(char *line, t_shell *shell)
{
	t_token	tkn;
	int		i;

	tkn.token = NULL;
	if (!ft_syntax(line))
		return (0);
	ft_token_init_all(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_find(&tkn, &line[i]);
		if (tkn.end)
		{
			if (!ft_token_assembler(&tkn, shell))
				return (ft_perror(ERR_SYS_MALLOC));
			ft_token_init_all(&tkn);
		}
	}
	return (1);
}
