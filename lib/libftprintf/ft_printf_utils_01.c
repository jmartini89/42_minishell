/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_01.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 16:06:30 by jmartini          #+#    #+#             */
/*   Updated: 2021/03/23 16:06:32 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pf_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_pf_strlen(const char *str)
{
	size_t	it;

	it = 0;
	while (str[it])
		it++;
	return (it);
}

int	ft_pf_atoi(const char *str)
{
	int	it;
	int	n;

	it = 0;
	n = 0;
	while (ft_pf_isdigit(str[it]))
	{
		n = (n * 10) + (str[it] - '0');
		it++;
	}
	return (n);
}
