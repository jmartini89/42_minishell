/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 19:13:31 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/21 18:19:17 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	t_byte			*a;
	const t_byte	*b;

	a = dst;
	b = src;
	if (!dst && !src)
		return (0);
	while (n)
	{
		*a++ = *b++;
		n--;
	}
	return (dst);
}
