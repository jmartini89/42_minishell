#include "minishell.h"

int
	ft_is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (R_OUT);
	if (c == '<')
		return (R_IN);
	return (WORD);
}
