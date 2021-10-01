#include "minishell.h"

static void	ft_builtin_launch(t_shell *shell, char **arg, int status)
{
	if (status == (BLTIN_CD))
		;
	if (status == (BLTIN_ECHO))
		;
	if (status == (BLTIN_ENV))
		ft_env(shell, arg);
	if (status == (BLTIN_EXIT))
		ft_exit(shell);
	if (status == (BLTIN_EXEC))
		ft_exec(shell);
	if (status == (BLTIN_EXPORT))
		ft_export(shell, arg);
	if (status == (BLTIN_PWD))
		;
	if (status == (BLTIN_UNSET))
		;
}

int	ft_builtin(t_shell *shell, char **arg)
{
	int	status;

	status = 0;
	if (!ft_memcmp(arg[0], "cd", 2) && ft_strlen(arg[0]) == 2)
		status = (BLTIN_CD);
	if (!ft_memcmp(arg[0], "echo", 4) && ft_strlen(arg[0]) == 4)
		status = (BLTIN_ECHO);
	if (!ft_memcmp(arg[0], "env", 3) && ft_strlen(arg[0]) == 3)
		status = (BLTIN_ENV);
	if (!ft_memcmp(arg[0], "exit", 4) && ft_strlen(arg[0]) == 4)
		status = (BLTIN_EXIT);
	if (!ft_memcmp(arg[0], "export", 6) && ft_strlen(arg[0]) == 6)
		status = (BLTIN_EXPORT);
	if (!ft_memcmp(arg[0], "pwd", 3) && ft_strlen(arg[0]) == 3)
		status = (BLTIN_PWD);
	if (!ft_memcmp(arg[0], "unset", 5) && ft_strlen(arg[0]) == 5)
		status = (BLTIN_UNSET);
	ft_builtin_launch(shell, arg, status);
	return (status);
}
