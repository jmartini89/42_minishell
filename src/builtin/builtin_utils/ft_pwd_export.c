#include "minishell.h"

void	ft_pwd_export_old(t_shell *shell)
{
	char	**custom;
	char	*tmp;
	char	*old_pwd;

	custom = ft_calloc(3, sizeof(*custom));
	custom[0] = "export";
	old_pwd = ft_getenv(shell, "PWD");
	if (!old_pwd)
		return (free (custom));
	tmp = ft_strjoin("OLDPWD=", old_pwd);
	if (!tmp)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	custom[1] = tmp;
	ft_export(shell, custom);
	free (tmp);
	free (custom);
}

void	ft_pwd_export_new(t_shell *shell)
{
	char	**custom;
	char	*tmp;
	char	*cwd;

	custom = ft_calloc(3, sizeof(*custom));
	custom[0] = "export";
	cwd = ft_getcwd(shell);
	if (!cwd)
		return (free (custom));
	tmp = ft_strjoin("PWD=", cwd);
	free (cwd);
	if (!tmp)
		ft_perrno_exit(ERR_SYS_MALLOC, EXIT_FAILURE);
	custom[1] = tmp;
	ft_export(shell, custom);
	free (tmp);
	free (custom);
}
