/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 18:40:33 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/21 16:53:45 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	t_byte			*d;
	t_byte			*revd;
	const t_byte	*s;
	const t_byte	*revs;

	d = dst;
	revd = d + (len - 1);
	s = src;
	revs = s + (len - 1);
	if (dst || src)
	{
		if (d < s)
			ft_memcpy(d, s, len);
		else
			while (len--)
				*revd-- = *revs--;
	}
	return (dst);
}
