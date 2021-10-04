#include "minishell.h"

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
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_perror_exit(ERR_SYS_MALLOC);
	ft_printf("%s\n", cwd);
	free (cwd);
	ft_env_return(shell, 0);
}
