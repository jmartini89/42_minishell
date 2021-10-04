#include "minishell.h"

void	ft_cd_home(t_shell *shell, char *arg)
{
	char	*home;

	home = ft_getenv(shell, "HOME");
	if (home)
	{
		chdir(home);
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
		ft_printf("%u\n", S_ISDIR(statbuf.st_mode));
		S_ISDIR(statbuf.st_mode);
		S_ISREG(statbuf.st_mode);
	}
}
