/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/20 15:26:53 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/20 15:26:55 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (!size)
	{
		ptr = malloc(size);
		return (ptr);
	}
	ptr = malloc(size * count);
	if (!ptr)
		return (0);
	ft_bzero(ptr, size * count);
	return (ptr);
}
