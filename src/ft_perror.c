#include "../inc/minishell.h"

void	ft_perror(int err)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
}
