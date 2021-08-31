/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:58:17 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/25 16:00:34 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_allocnt(long int n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_convert_it(char *str, long int n, int size)
{
	if (!n)
	{
		*str = '0';
		return (str);
	}
	if (n < 0)
	{
		*str = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[size - 1] = (n % 10) + '0';
		n = n / 10;
		size--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		size;

	size = ft_allocnt((long int)n);
	str = ft_calloc(size + 1, sizeof(*str));
	if (!str)
		return (NULL);
	return (ft_convert_it(str, (long int)n, size));
}
