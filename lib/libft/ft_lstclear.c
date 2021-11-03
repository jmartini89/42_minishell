/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmartini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 13:13:05 by jmartini          #+#    #+#             */
/*   Updated: 2021/01/29 13:14:13 by jmartini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	if (*lst)
	{
		ptr = *lst;
		while (ptr)
		{
			tmp = ptr;
			if (del)
				(del)(ptr->content);
			ptr = ptr->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
