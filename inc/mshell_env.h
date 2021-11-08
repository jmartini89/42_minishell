/* MSHELL_ENV */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_env.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:01 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:02 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_ENV_H
# define MSHELL_ENV_H

int		ft_env_init(t_shell *shell, char **envp);
char	*ft_getenv(t_shell *shell, char *str);
void	ft_env_return(t_shell *shell, int ret);
char	*ft_itoa_shlvl(char *str);

#endif