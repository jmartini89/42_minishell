/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 18:30:51 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/29 13:20:05 by jmartini         ###   ########.fr       */
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

char	*ft_strnstr(const char *haystack,
			const char *needle, size_t len)
{
	size_t	little;

	if (!*needle)
		return ((char *)haystack);
	if (!*haystack)
		return (0);
	little = ft_strlen(needle);
	while (len)
	{
		if (!(ft_strncmp(haystack, needle, ft_min(little, len)))
			&& len >= little)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
