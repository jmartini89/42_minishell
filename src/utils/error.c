#include "minishell.h"

void	ft_perrno_exit(int err, int status)
{
	ft_putstr_fd(M_SHELL_NAME" : ", 2);
	ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
	exit (status);
}

void	ft_perrno(int err, char *libc)
{
	ft_putstr_fd(M_SHELL_NAME": ", 2);
	if (libc)
	{
		ft_putstr_fd(libc, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(err), 2);
	}
	else
		ft_putstr_fd((char *)g_errstr[err], 2);
	ft_putstr_fd("\n", 2);
}
