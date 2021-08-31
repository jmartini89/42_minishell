/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:43:07 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/29 13:15:49 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_srcchar(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static char	*src_start(char *str, char *set)
{
	while (ft_srcchar(set, *str))
		str++;
	return (str);
}

static char	*src_end(char *str, char *set)
{
	while (ft_srcchar(set, *str))
		str--;
	str++;
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	char	*start;
	char	*end;
	int		size;

	if (!s1)
		return (0);
	start = src_start((char *)s1, (char *)set);
	end = src_end((char *)&s1[ft_strlen(s1) - 1], (char *)set);
	size = end - start;
	if (start >= &s1[ft_strlen(s1)])
	{
		ptr = ft_calloc(1, sizeof(*ptr));
		if (!ptr)
			return (0);
		return (ptr);
	}
	ptr = malloc(sizeof(*ptr) * (size) + 1);
	if (!ptr)
		return (0);
	ft_memcpy(ptr, start, size);
	ptr[size] = '\0';
	return (ptr);
}
