#include "minishell.h"

char *
	ft_getcwd(t_shell *shell)
{
	char	*cwd;
	int		err;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		err = errno;
		if (err == ENOMEM)
			ft_error_exit(errno, "malloc", EXIT_FAILURE);
		if (err == ENOENT)
			ft_error(ERR_BLTIN_PWD_NDIR, NULL);
		else
			ft_error(err, "pwd");
		return (NULL);
	}
	return (cwd);
}
