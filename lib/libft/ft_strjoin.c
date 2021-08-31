/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:42:54 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/22 15:42:59 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
		return (0);
	ptr = malloc(sizeof(*ptr) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!ptr)
		return (0);
	ft_memcpy(ptr, s1, ft_strlen(s1));
	ft_memcpy(&ptr[ft_strlen(s1)], s2, ft_strlen(s2));
	ptr[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (ptr);
}
