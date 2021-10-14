#include "minishell.h"

void
	ft_pwd(t_shell *shell, char **argv)
{
	char	*cwd;
	int		argc;

	argc = ft_argc(argv);
	if (argc > 1)
	{
		ft_perrno(ERR_BLTIN_ARGS, NULL);
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
	else
		ft_env_return(shell, 1);
}
