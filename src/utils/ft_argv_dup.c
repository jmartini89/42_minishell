/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_argv_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:44 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:49:45 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **
	ft_argv_dup(char **argv)
{
	char	**heap;
	int		len;

	len = ft_argc(argv);
	heap = ft_calloc(len + 1, sizeof(*heap));
	if (!heap)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	len = -1;
	while (argv[++len])
	{
		heap[len] = ft_strdup(argv[len]);
		if (!heap[len])
			ft_error_exit(errno, "malloc", EXIT_FAILURE);
	}
	return (heap);
}
