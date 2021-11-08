/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:48:36 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:48:37 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_lstprint(void *content)
{
	ft_printf("%s\n", (char *)content);
}

void
	ft_rdr_print(int type, char *name)
{
	ft_printf("REDIR\ttype\t%d\tname\t%s\n", type, name);
}
