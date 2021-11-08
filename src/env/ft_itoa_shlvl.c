/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_shlvl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:08 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:09 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *
	ft_itoa_shlvl(char *str)
{
	int	i;
	int	valid;
	int	atoi;

	valid = 1;
	i = -1;
	while (valid && str[++i])
	{
		if (!i && (str[i] == '+' || str[i] == '-'))
			i++;
		if (valid && str[i] && !ft_isdigit(str[i]))
			valid = 0;
	}
	if (!valid)
		return (ft_itoa(1));
	atoi = ft_atoi(str);
	if (atoi < 0)
		return (ft_itoa(0));
	return (ft_itoa(atoi + 1));
}
