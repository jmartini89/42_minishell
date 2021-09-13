#include "minishell.h"

int	ft_is_operator(char c)
{
	if (c == '|')
		return (PIPE);
	if (c == '>')
		return (REDIR_R);
	if (c == '<')
		return (REDIR_L);
	return (0);
}
