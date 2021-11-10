/* MINISHELL */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:46:50 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:46:51 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* SYS LIBRARIES */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>

/* LOCAL LIBRARIES*/
# include "libft.h"
# include "ft_printf.h"

/* SUB_HEADERS */
# include "mshell_main.h"
# include "mshell_utils.h"
# include "mshell_env.h"
# include "mshell_parser.h"
# include "mshell_builtin.h"
# include "mshell_exec.h"
# include "mshell_liblist.h"

#endif