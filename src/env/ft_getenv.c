#include "minishell.h"

char *
	ft_getenv(t_shell *shell, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	if (!ft_memcmp(str, "?", 1) && ft_strlen(str) == 1)
		return (shell->ret_str);
	while (shell->env[++i])
	{
		if (!ft_memcmp(shell->env[i], str, len)
			&& shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
	}
	return (NULL);
}
