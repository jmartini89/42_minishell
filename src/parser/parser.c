#include "minishell.h"

int	ft_parser(char *line_read)
{
	if (!ft_validity_check(line_read))
		return (0);
	ft_token(line_read);
	return (1);
}
