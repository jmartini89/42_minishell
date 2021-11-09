/* MSHELL_EXEC */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_exec.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:03 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:04 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_EXEC_H
# define MSHELL_EXEC_H

enum	e_builtin {
	BLTIN_EXEC,
	BLTIN_CD,
	BLTIN_ECHO,
	BLTIN_ENV,
	BLTIN_EXIT,
	BLTIN_EXPORT,
	BLTIN_PWD,
	BLTIN_UNSET,
};

void	ft_exec(t_shell *shell);

/* REDIRECTIONS */
int		ft_redir(t_cmd *cmd);

/* DO_EXEC */
void	ft_do_exec(t_shell *shell, pid_t *pid_arr);

/* CHILD */
void	ft_child(t_shell *shell, int i, int *pipefd, int input);

/* BUILTIN */
int		ft_builtin_check(char **argv);
void	ft_builtin_launch(
			t_shell *shell, char **argv, int status, int process);

/* PATH */
int		ft_is_path(char *arg);
int		ft_exec_env_path(t_shell *shell, char **arg);

#endif