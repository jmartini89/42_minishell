#include "minishell.h"

int	ft_is_metachar(char c)
{
	if (c == '\\' || c == '|' || c == '&' || c == ';'
		|| c == '(' || c == ')' || c == '<' || c == '>')
		return (1);
	return (0);
}
