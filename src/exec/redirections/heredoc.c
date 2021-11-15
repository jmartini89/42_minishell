/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 18:26:10 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/10 18:26:11 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	ft_wait_heredoc(pid_t pid)
{
	int	wstatus;
	int	wexit;

	wexit = waitpid(pid, &wstatus, WUNTRACED);
	if (wexit == -1)
		ft_error_exit(errno, "waitpid", EXIT_FAILURE);
	if (WIFSTOPPED(wstatus))
		return (WSTOPSIG(wstatus) + 128);
	if (WIFSIGNALED(wstatus))
	{
		if (WTERMSIG(wstatus) == SIGINT)
			ft_printf("\n");
		return (WTERMSIG(wstatus) + 128);
	}
	if (WIFEXITED(wstatus))
		return (WEXITSTATUS(wstatus));
	return (EXIT_FAILURE);
}

static int
	ft_heredoc_fork(t_shell *shell, t_redir *lst)
{
	pid_t	pid;
	int		ret;

	ret = 0;
	pid = fork();
	if (pid == -1)
		ft_error_exit(errno, "fork", EXIT_FAILURE);
	if (pid == 0)
		ft_heredoc_child(lst);
	else
		ret = ft_wait_heredoc(pid);
	ft_env_return(shell, ret);
	if (ret > 0)
		return (0);
	return (1);
}

int
	ft_heredoc(t_shell *shell, t_redir *lst)
{
	if (lst == NULL)
		return (1);
	while (lst)
	{
		if (lst->type == HERE)
			if (!ft_heredoc_fork(shell, lst))
				return (0);
		lst = lst->next;
	}
	return (1);
}
