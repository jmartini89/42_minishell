#include "minishell.h"

char	*ft_getenv(t_shell *shell, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	while (shell->env[++i])
	{
		if (!ft_memcmp(shell->env[i], str, len)
			&& shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
	}
	return (NULL);
}
