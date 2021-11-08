/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rdr_add_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:24 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:25 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_rdr_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	ptr = NULL;
	if (*lst)
	{
		ptr = ft_rdr_last(*lst);
		ptr->next = new;
	}
	else
		*lst = new;
}
