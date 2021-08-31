/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:50:21 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/29 13:16:09 by jmartini         ###   ########.fr       */
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

static int	ft_sublen(char *s, int c)
{
	int	i;

	i = 0;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static int	ft_subcount(char *s, int c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!(ft_srcchar((char *)s, c)))
		return (1);
	while (s[i])
	{
		if (s[i] != c)
		{
			count++;
			i += ft_sublen(&s[i], c);
		}
		i++;
	}
	return (count);
}

static char	*ft_nextsub(char *s, int c)
{
	char	*ptr;

	while (*s)
	{
		if (*s != c)
		{
			ptr = s;
			return (ptr);
		}
		s++;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**sstr;
	char	*ptr;
	int		strs_cnt;
	int		i;

	i = 0;
	ptr = (char *)s;
	if (!s)
		return (NULL);
	strs_cnt = ft_subcount((char *)s, c);
	sstr = ft_calloc(strs_cnt + 1, sizeof(*sstr));
	if (!sstr)
		return (NULL);
	ptr = ft_nextsub(ptr, c);
	while (ptr)
	{
		sstr[i] = ft_calloc(ft_sublen(ptr, c) + 1, sizeof(**sstr));
		if (!sstr[i])
			return (NULL);
		ft_strlcpy(sstr[i], ptr, ft_sublen(ptr, c) + 1);
		ptr = (char *)&ptr[ft_sublen(ptr, c)];
		i++;
		ptr = ft_nextsub(ptr, c);
	}
	return (sstr);
}
