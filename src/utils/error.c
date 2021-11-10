/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:39 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:40 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_error_exit(int err, char *libc, int status)
{
	int	errcpy;

	errcpy = err;
	ft_putstr_fd(M_SHELL_NAME": ", 2);
	if (libc)
	{
		ft_putstr_fd(libc, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errcpy), 2);
	}
	else
		ft_putstr_fd((char *)g_errstr[errcpy], 2);
	ft_putstr_fd("\n", 2);
	exit (status);
}

void
	ft_error(int err, char *libc)
{
	int	errcpy;

	errcpy = err;
	ft_putstr_fd(M_SHELL_NAME": ", 2);
	if (libc)
	{
		ft_putstr_fd(libc, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errcpy), 2);
	}
	else
		ft_putstr_fd((char *)g_errstr[errcpy], 2);
	ft_putstr_fd("\n", 2);
}
