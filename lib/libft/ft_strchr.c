/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 14:58:51 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/19 14:58:54 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	flag;

	flag = c;
	while (*s)
	{
		if (*s == flag)
			return ((char *)s);
		s++;
	}
	if (!*s && *s == flag)
		return ((char *)s);
	return (0);
}
