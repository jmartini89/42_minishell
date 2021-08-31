/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:33:21 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/21 18:21:26 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const t_byte	*ptr;
	t_byte			flag;

	ptr = s;
	flag = c;
	while (n--)
	{
		if (*ptr == flag)
			return ((t_byte *)ptr);
		ptr++;
	}
	ptr = 0;
	return ((t_byte *)ptr);
}
