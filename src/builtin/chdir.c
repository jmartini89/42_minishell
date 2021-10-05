#include "minishell.h"

void	ft_chdir_home(t_shell *shell, char *arg)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (home)
	{
		chdir(home);
		ft_env_return(shell, 0);
	}
	else
	{
		ft_perror(ERR_BLTIN_CD_HOME);
		ft_env_return(shell, 1);
		return ;
	}
}

void	ft_chdir(t_shell *shell, char **argv)
{
	struct stat	statbuf;
	int			argc;

	argc = ft_argc(argv);
	if (argc > 2)
	{
		ft_perror(ERR_BLTIN_CD_ARGS);
		ft_env_return(shell, 1);
		return ;
	}
	if (argc == 1)
		ft_cd_home(shell, argv[1]);
	else
	{
		stat(argv[1], &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			chdir(argv[1]);
			// UPDATE PWD & OLDPWD
			ft_env_return(shell, 0);
		}
		else
		{
			ft_perror(ERR_BLTIN_CD_NDIR);
			ft_env_return(shell, 1);
		}
	}
}
