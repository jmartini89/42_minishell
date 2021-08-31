/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 16:28:45 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/26 18:12:29 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s)
		return (0);
	ptr = ft_calloc(ft_strlen(s) + 1, sizeof(*ptr));
	if (!ptr)
		return (0);
	while (*s)
	{
		ptr[i] = (f)(i, *s);
		i++;
		s++;
	}
	return (ptr);
}
