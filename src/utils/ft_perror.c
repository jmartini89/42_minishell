#include "minishell.h"

int	ft_perror(int err)
{
	ft_putstr_fd(M_SHELL_NAME" : ", 2);
	ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
	if (err == ERR_SYS_MALLOC)
		return (-1);
	return (0);
}
