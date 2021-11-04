#include "minishell.h"

void
	ft_builtin_launch(t_shell *shell, char **argv, int status, int process)
{
	if (status == (BLTIN_CD))
		ft_cd(shell, argv, process);
	if (status == (BLTIN_ECHO))
		ft_echo(shell, argv, process);
	if (status == (BLTIN_ENV))
		ft_env(shell, argv, process);
	if (status == (BLTIN_EXIT))
		ft_exit(shell, argv);
	if (status == (BLTIN_EXPORT))
		ft_export(shell, argv, process);
	if (status == (BLTIN_PWD))
		ft_pwd(shell, argv, process);
	if (status == (BLTIN_UNSET))
		ft_unset(shell, argv, process);
}

int
	ft_builtin_check(char **argv)
{
	int	status;

	status = 0;
	if (argv == NULL)
		return (status);
	if (!ft_memcmp(argv[0], "cd", 2) && ft_strlen(argv[0]) == 2)
		status = (BLTIN_CD);
	if (!ft_memcmp(argv[0], "echo", 4) && ft_strlen(argv[0]) == 4)
		status = (BLTIN_ECHO);
	if (!ft_memcmp(argv[0], "env", 3) && ft_strlen(argv[0]) == 3)
		status = (BLTIN_ENV);
	if (!ft_memcmp(argv[0], "exit", 4) && ft_strlen(argv[0]) == 4)
		status = (BLTIN_EXIT);
	if (!ft_memcmp(argv[0], "export", 6) && ft_strlen(argv[0]) == 6)
		status = (BLTIN_EXPORT);
	if (!ft_memcmp(argv[0], "pwd", 3) && ft_strlen(argv[0]) == 3)
		status = (BLTIN_PWD);
	if (!ft_memcmp(argv[0], "unset", 5) && ft_strlen(argv[0]) == 5)
		status = (BLTIN_UNSET);
	return (status);
}
