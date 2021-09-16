#include "minishell.h"

int	ft_is_space_tab(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	else
		return (0);
}
