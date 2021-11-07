/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rdr_iter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:30 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:31 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_rdr_iter(t_redir *lst, void (*f)(int type, char *name))
{
	while (lst)
	{
		(f)(lst->type, lst->name);
		lst = lst->next;
	}
}
