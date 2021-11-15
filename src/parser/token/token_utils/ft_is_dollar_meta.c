/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_dollar_meta.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 02:00:06 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/15 02:00:07 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	ft_is_dollar_meta(char c)
{
	char	*sample;

	sample = "#$%*+,-./:=@^~";
	while (*sample)
	{
		if (c == *sample)
			return (TRUE);
		sample++;
	}
	return (FALSE);
}
