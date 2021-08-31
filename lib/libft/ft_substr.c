/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 18:38:03 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/29 13:15:33 by jmartini         ###   ########.fr       */
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
	{
		ptr = ft_calloc(1, sizeof(*ptr));
		if (ptr)
			return (0);
		return (ptr);
	}
	ptr = ft_calloc(ft_min(len, ft_strlen(s)) + 1, sizeof(*ptr));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, &s[start], len + 1);
	return (ptr);
}
