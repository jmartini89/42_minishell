#include "minishell.h"

void	ft_pwd_update_old()
{
	//
}

void	ft_cd_home(t_shell *shell, char *arg)
{
	char	*home;
	int		err;

	home = ft_getenv(shell, "HOME");
	if (home)
	{
		if (chdir(home) < 0)
		{
			err = errno;
			ft_strerror("cd", err);
			ft_env_return(shell, 1);
			return ;
		}
		ft_env_return(shell, 0);
	}
	else
	{
		ft_perror(ERR_BLTIN_CD_HOME);
		ft_env_return(shell, 1);
		return ;
	}
}

void	ft_cd(t_shell *shell, char **argv)
{
	int			argc;
	int			err;

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
		if (chdir(argv[1]) < 0)
		{
			err = errno;
			ft_strerror("cd", err);
		}
	}
}
