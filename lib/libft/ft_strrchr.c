/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:03:37 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/21 18:24:32 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	flag;
	int		len;

	flag = c;
	len = ft_strlen(s);
	s = &s[len];
	if (*s == flag)
		return ((char *)s);
	while (len-- >= 0)
	{
		if (*s == flag)
			return ((char *)s);
		s--;
	}
	return (0);
}
