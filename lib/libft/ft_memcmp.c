/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:33:50 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/21 18:22:45 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const t_byte	*ptr1;
	const t_byte	*ptr2;

	ptr1 = s1;
	ptr2 = s2;
	if (n)
	{
		while (n--)
		{
			if ((*ptr1) - (*ptr2))
				return ((*ptr1) - (*ptr2));
			ptr1++;
			ptr2++;
		}
	}
	return (0);
}
