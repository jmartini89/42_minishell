#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	ft_printf("exit\n");
	exit (ft_atoi(shell->ret_str));
}
