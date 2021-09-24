#include "minishell.h"

int	ft_is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (REDIR_OUT);
	if (c == '<')
		return (REDIR_IN);
	return (WORD);
}
