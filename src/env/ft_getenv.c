/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:05 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:06 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *
	ft_getenv(t_shell *shell, char *str)
{
	int	i;
	int	len;

	len = ft_strlen(str);
	i = -1;
	if (!ft_memcmp(str, "?", 1) && ft_strlen(str) == 1)
		return (shell->ret_str);
	while (shell->env[++i])
	{
		if (!ft_memcmp(shell->env[i], str, len)
			&& shell->env[i][len] == '=')
			return (&shell->env[i][len + 1]);
	}
	return (NULL);
}
