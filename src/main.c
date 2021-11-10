/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:49:55 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/09 17:13:29 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	int		ret;

	(void)argc;
	(void)argv;
	ft_env_init(&shell, envp);
	ft_signal();
	ft_header();
	ret = ft_prompt(&shell);
	return (ret); // CHANGE TO EXIT
}
