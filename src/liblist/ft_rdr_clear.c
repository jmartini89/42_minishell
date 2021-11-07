/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rdr_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:27 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:28 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_rdr_clear(t_redir **lst, void (*del)(void *))
{
	t_redir	*ptr;
	t_redir	*tmp;

	if (*lst)
	{
		ptr = *lst;
		while (ptr)
		{
			tmp = ptr;
			(del)(ptr->name);
			ptr = ptr->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
