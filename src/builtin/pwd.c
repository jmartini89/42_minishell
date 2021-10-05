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
		ft_env_return(shell, 1);
		return (NULL);
	}
	return (cwd);
}

void	ft_pwd(t_shell *shell, char **argv)
{
	char	*cwd;
	int		argc;

	argc = ft_argc(argv);
	if (argc > 1)
	{
		ft_perror(ERR_BLTIN_ARGS);
		ft_env_return(shell, 1);
		return ;
	}
	cwd = ft_getcwd(shell);
	if (cwd)
	{
		ft_printf("%s\n", cwd);
		free (cwd);
		ft_env_return(shell, 0);
	}
}
