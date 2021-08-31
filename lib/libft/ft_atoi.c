/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 19:17:02 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/20 19:17:04 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(int c)
{
	if ((c >= '\t' && c <= '\r') || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int	it;
	int	sign;
	int	n;

	it = 0;
	sign = 1;
	n = 0;
	while (ft_isspace(str[it]))
		it++;
	if (str[it] == '-' && ft_isdigit(str[it + 1]))
	{
		sign = -1;
		it++;
	}
	if (str[it] == '+' && ft_isdigit(str[it + 1]))
		it++;
	while (ft_isdigit(str[it]))
	{
		n = (n * 10) + (str[it] - '0');
		it++;
	}
	return (n * sign);
}
