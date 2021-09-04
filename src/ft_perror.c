#include "../inc/minishell.h"

int	ft_perror(int err)
{
	ft_putstr_fd("Error : ", 2);
	ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
