/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:33 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:34 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	ft_cd_home(t_shell *shell)
{
	int		err;
	char	*env;

	env = ft_getenv(shell, "HOME");
	if (env)
	{
		if (chdir(env) < 0)
		{
			err = errno;
			ft_error(err, "cd");
			ft_env_return(shell, 1);
			return ;
		}
		ft_env_return(shell, 0);
	}
	else
	{
		ft_error(ERR_BLTIN_CD_HOME, NULL);
		ft_env_return(shell, 1);
		return ;
	}
}

static void
	ft_chdir(t_shell *shell, char *arg)
{
	int	err;

	if (chdir(arg) < 0)
	{
		err = errno;
		ft_error(err, "cd");
		ft_env_return(shell, 1);
	}
	else
		ft_env_return(shell, 0);
}

void
	ft_cd(t_shell *shell, char **argv, int process)
{
	int	argc;

	argc = ft_argc(argv);
	if (argc > 2)
	{
		ft_error(ERR_BLTIN_CD_ARGS, NULL);
		ft_env_return(shell, 1);
		return ;
	}
	ft_pwd_export_old(shell);
	if (argc == 1)
		ft_cd_home(shell);
	else
		ft_chdir(shell, argv[1]);
	ft_pwd_export_new(shell);
	if (process)
		exit (ft_atoi(shell->ret_str));
}
