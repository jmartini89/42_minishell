#include "minishell.h"

void	ft_builtin(t_shell *shell, char **argv)
{
	if (!ft_memcmp(argv[0], "cd", 2) && ft_strlen(argv[0]) == 2)
		ft_cd(shell, argv);
	else if (!ft_memcmp(argv[0], "echo", 4) && ft_strlen(argv[0]) == 4)
		ft_echo(shell, argv);
	else if (!ft_memcmp(argv[0], "env", 3) && ft_strlen(argv[0]) == 3)
		ft_env(shell, argv);
	else if (!ft_memcmp(argv[0], "exit", 4) && ft_strlen(argv[0]) == 4)
		ft_exit(shell, argv);
	else if (!ft_memcmp(argv[0], "export", 6) && ft_strlen(argv[0]) == 6)
		ft_export(shell, argv);
	else if (!ft_memcmp(argv[0], "pwd", 3) && ft_strlen(argv[0]) == 3)
		ft_pwd(shell, argv);
	else if (!ft_memcmp(argv[0], "unset", 5) && ft_strlen(argv[0]) == 5)
		ft_unset(shell, argv);
	else
		ft_exec(shell, argv);
}
