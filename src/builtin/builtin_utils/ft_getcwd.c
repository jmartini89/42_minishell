#include "minishell.h"

char	*ft_getcwd(t_shell *shell)
{
	char	*cwd;
	int		err;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		err = errno;
		if (err == ENOMEM)
			ft_perror_exit(ERR_SYS_MALLOC);
		if (err == ENOENT)
			ft_perror(ERR_BLTIN_PWD_NDIR);
		else
			ft_strerror("pwd", err);
		return (NULL);
	}
	return (cwd);
}
