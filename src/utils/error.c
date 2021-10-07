#include "minishell.h"

int	ft_perrno_sys(char *type, int err)
{
	ft_putstr_fd(M_SHELL_NAME" : ", 2);
	ft_putstr_fd(type, 2);
	ft_putstr_fd(" : ", 2);
	ft_putstr_fd(strerror(err), 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

void	ft_perrno_exit(int err)
{
	ft_putstr_fd(M_SHELL_NAME" : ", 2);
	ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
	exit (EXIT_FAILURE);
}

int	ft_perrno_int(int err)
{
	ft_putstr_fd(M_SHELL_NAME" : ", 2);
	ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
