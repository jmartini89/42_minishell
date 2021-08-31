/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:39:08 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/19 18:39:10 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const t_byte	*ptr1;
	const t_byte	*ptr2;

	ptr1 = (t_byte *)s1;
	ptr2 = (t_byte *)s2;
	if (n)
	{
		while (n-- && (*ptr1 || *ptr2))
		{
			if ((*ptr1) - (*ptr2))
				return ((*ptr1) - (*ptr2));
			ptr1++;
			ptr2++;
		}
	}
	return (0);
}
