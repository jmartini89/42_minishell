/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:50 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:51 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	ft_header(void)
{
	ft_printf("\e[1m42 Minishell\e[0m\n\e[3mas beautiful as a shell\e[0m\n");
	ft_printf("\n");
	ft_printf("Emulating Bash Version 5.1\n");
	ft_printf("Bash Reference Manual:\n");
	ft_printf("<http://www.gnu.org/software/bash/>\n");
	ft_printf("Minishell Reference Manual:\n");
	ft_printf("<http://github.com/jmartini89/42_minishell/wiki>\n");
	ft_printf("\n");
	ft_printf("Made by jmartini & mcrisari\n");
}
