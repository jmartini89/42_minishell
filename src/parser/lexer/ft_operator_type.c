#include "minishell.h"

int
	ft_operator_type(char *arg)
{
	int	type;

	type = ft_is_operator(*arg);
	if (type > PIPE)
	{
		if (ft_strlen(arg) > 1)
			type *= 2;
	}
	return (type);
}
