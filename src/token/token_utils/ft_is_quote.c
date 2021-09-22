#include "minishell.h"

int	ft_is_quote(char c)
{
	if (c == '\'')
		return (QTS_SINGLE);
	if (c == '\"')
		return (QTS_DOUBLE);
	return (0);
}
