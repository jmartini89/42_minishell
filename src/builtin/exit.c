#include "minishell.h"

void	ft_exit(t_shell *shell, char **argv)
{
	int	argc;

	argc = 0;
	while (argv && argv[argc])
		argc++;
	if (argc > 1)
	{
		ft_perror(ERR_BLTIN_ARGS);
		ft_env_return(shell, 1);
		return ;
	}
	ft_printf("exit\n");
	exit (ft_atoi(shell->ret_str));
}