/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:03 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:04 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_env_return(t_shell *shell, int ret)
{
	free (shell->ret_str);
	shell->ret_str = ft_itoa(ret);
	if (!shell->ret_str)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
}

static void
	ft_env_custom_lvl(t_shell *shell)
{
	char	**custom;
	char	*itoa;
	char	*tmp;
	char	*lvl;

	custom = ft_calloc(3, sizeof(*custom));
	custom[0] = "export";
	lvl = ft_getenv(shell, "SHLVL");
	if (lvl)
	{
		itoa = ft_itoa_shlvl(lvl);
		if (!itoa)
			ft_error_exit(errno, "malloc", EXIT_FAILURE);
	}
	else
		itoa = "1";
	tmp = ft_strjoin("SHLVL=", itoa);
	if (!tmp)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	if (lvl)
		free (itoa);
	custom[1] = tmp;
	ft_export(shell, custom, 0);
	free (tmp);
	free (custom);
}

int
	ft_env_init(t_shell *shell, char **envp)
{
	shell->ret_str = NULL;
	ft_env_return(shell, 0);
	shell->env = ft_argv_dup(envp);
	ft_env_custom_lvl(shell);
	ft_pwd_export_new(shell);
	return (1);
}
