/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getcwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:25 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:26 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *
	ft_getcwd(void)
{
	char	*cwd;
	int		err;

	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		err = errno;
		if (err == ENOMEM)
			ft_error_exit(errno, "malloc", EXIT_FAILURE);
		if (err == ENOENT)
			ft_error(ERR_BLTIN_PWD_NDIR, NULL);
		else
			ft_error(err, "pwd");
		return (NULL);
	}
	return (cwd);
}
