/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_operator_type.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:02 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:03 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_operator_type(char *arg)
{
	int	type;

	type = ft_is_operator(*arg);
	if (type > PIPE)
	{
		if (ft_strlen(arg) > 1)
			type *= 2;
	}
	return (type);
}
