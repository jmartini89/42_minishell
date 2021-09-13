#include "minishell.h"

int	ft_token(char *line)
{
	t_token	tkn;
	int		i;

	if (!ft_parser(line))
		return (0);
	ft_token_init_all(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_find(&tkn, &line[i]);
		if (tkn.end)
		{
			ft_token_assembler(&tkn);
			ft_token_init_all(&tkn);
		}
	}
	return (1);
}
