/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 18:34:05 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/20 18:34:07 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ptr;

	ptr = malloc(sizeof(*s1) * (ft_strlen(s1) + 1));
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, ft_strlen(s1) + 1);
	return (ptr);
}
