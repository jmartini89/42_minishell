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
			ft_perrno_exit(ERR_SYS_MALLOC);
		if (err == ENOENT)
			ft_perrno(ERR_BLTIN_PWD_NDIR, NULL);
		else
			ft_perrno(err, "pwd");
		return (NULL);
	}
	return (cwd);
}
