/* MSHELL_MAIN */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_main.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:11 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:54:40 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_MAIN_H
# define MSHELL_MAIN_H
# define M_SHELL_NAME "miniscell"
# define M_SHELL_PROMPT "\001\e[32m\002miniscell\001\e[0m\002$ "

typedef struct s_redir
{
	int		type;
	char	*name;
	void	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redir;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*cwd;
	char	*ret_str;
	t_cmd	*cmd;
	int		cmd_cnt;
}	t_shell;

void	ft_prompt(t_shell *shell);

#endif