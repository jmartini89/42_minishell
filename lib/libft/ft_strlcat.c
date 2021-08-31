/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:23:29 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/29 13:14:56 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_min(const size_t s1, const size_t s2)
{
	if (s1 < s2)
		return (s1);
	else
		return (s2);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;

	srclen = ft_strlen(src);
	dstlen = ft_strlen(dst);
	if (dstlen + 1 <= dstsize)
	{
		ft_strlcpy(&dst[dstlen], src, dstsize - dstlen);
		dst[dstsize - 1] = '\0';
	}
	return ((ft_min(dstsize, dstlen)) + srclen);
}
