/* MSHELL_BUILTIN */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_builtin.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:46:56 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:46:57 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_BUILTIN_H
# define MSHELL_BUILTIN_H

/* BUILT-IN */
void	ft_cd(t_shell *shell, char **argv, int process);
void	ft_echo(t_shell *shell, char **argv, int process);
void	ft_env(t_shell *shell, char **argv, int process);
void	ft_exit(t_shell *shell, char **argv, int process);
void	ft_export(t_shell *shell, char **argv, int process);
void	ft_pwd(t_shell *shell, char **argv, int process);
void	ft_unset(t_shell *shell, char **argv, int process);

/* UTILS */
char	*ft_getcwd(void);
void	ft_pwd_export_old(t_shell *shell);
void	ft_pwd_export_new(t_shell *shell);
int		ft_lencmp(char *arg, char *env);

#endif