#include "minishell.h"

void
	ft_exit(t_shell *shell, char **argv)
{
	int	argc;

	argc = ft_argc(argv);
	if (argc > 1)
	{
		ft_error(ERR_BLTIN_ARGS, NULL);
		ft_env_return(shell, 1);
		return ;
	}
	ft_printf("exit\n");
	exit (ft_atoi(shell->ret_str));
}
