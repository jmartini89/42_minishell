#include "minishell.h"

int	ft_token(char *line, t_shell *shell)
{
	t_token	tkn;
	int		i;

	shell->token = NULL;
	ft_token_init_all(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_find(&tkn, &line[i]);
		if (tkn.end)
		{
			if (!ft_token_assembler(&tkn, shell))
				return (0);
			ft_token_init_all(&tkn);
		}
	}
	/*
	** DEBUG
	int j = 0;
	while (tkn.token[j])
	{
		ft_printf("%s\n", tkn.token[j]);
		free (tkn.token[j]);
		j++;
	}
	free (tkn.token);
	*/
	return (1);
}
