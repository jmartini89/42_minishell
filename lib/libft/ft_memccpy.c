/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:19:45 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/21 18:19:58 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	t_byte			*a;
	const t_byte	*b;
	t_byte			flag;

	a = dst;
	b = src;
	flag = c;
	while (n)
	{
		if (*b == flag)
		{
			*a++ = *b++;
			return (a);
		}
		*a++ = *b++;
		n--;
	}
	a = 0;
	return (a);
}
