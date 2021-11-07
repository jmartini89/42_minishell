/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lencmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:28 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:29 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_lencmp(char *arg, char *env)
{
	int	arg_len;
	int	env_len;

	arg_len = 0;
	while (arg[arg_len])
		arg_len++;
	env_len = 0;
	while (env[env_len] && env[env_len] != '=')
		env_len++;
	if (arg_len >= env_len)
		return (arg_len);
	else
		return (env_len);
}
