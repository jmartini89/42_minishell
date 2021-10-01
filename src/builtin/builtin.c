#include "minishell.h"

int	ft_builtin(t_shell *shell, char **arg)
{
	if (!ft_memcmp(arg[0], "cd", 2) && ft_strlen(arg[0]) == 2)
		return (BLTIN_CD);
	if (!ft_memcmp(arg[0], "echo", 4) && ft_strlen(arg[0]) == 4)
		return (BLTIN_ECHO);
	if (!ft_memcmp(arg[0], "env", 3) && ft_strlen(arg[0]) == 3)
	{
		ft_export(shell, arg);
		return (BLTIN_ENV);
	}
	if (!ft_memcmp(arg[0], "exit", 4) && ft_strlen(arg[0]) == 4)
		return (BLTIN_EXIT);
	if (!ft_memcmp(arg[0], "export", 6) && ft_strlen(arg[0]) == 6)
	{
		ft_export(shell, arg);
		return (BLTIN_EXPORT);
	}
	if (!ft_memcmp(arg[0], "pwd", 3) && ft_strlen(arg[0]) == 3)
		return (BLTIN_PWD);
	if (!ft_memcmp(arg[0], "unset", 5) && ft_strlen(arg[0]) == 5)
		return (BLTIN_PWD);
	return (BLTIN_EXEC);
}
