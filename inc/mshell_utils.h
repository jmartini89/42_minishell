/* MSHELL_UTILS */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:13 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:14 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_UTILS_H
# define MSHELL_UTILS_H
# define FALSE 0
# define TRUE 1

enum	e_err {
	ERR_UNDEF,
	ERR_SYNTAX_QUOTES,
	ERR_SYNTAX_CHAR,
	ERR_SYNTAX_TKN,
	ERR_BLTIN_ARGS,
	ERR_BLTIN_CD_ARGS,
	ERR_BLTIN_CD_HOME,
	ERR_BLTIN_EXIT_ARGS,
	ERR_BLTIN_EXIT_NUM,
	ERR_BLTIN_EXPORT,
	ERR_BLTIN_PWD_NDIR,
	ERR_BLTIN_UNSET,
	ERR_EXEC_NOCMD,
	WRN_HEREDOC,
};
static const char *const	g_errstr[] = {
	"Undefined",
	"syntax error: unclosed quotes",
	"syntax error: undefined special character",
	"syntax error: unexpected token",
	"built-in: arguments are not supported",
	"cd: too many arguments",
	"cd: HOME not set",
	"exit: too many arguments",
	"exit: numeric argument required",
	"export: not a valid identifier",
	"pwd: the current working directory has been unlinked",
	"unset: not a valid identifier",
	"execve: command not found",
	"warning: here-document delimited by end-of-file",
};

/* HISTORY */
void	ft_history(char *line);

/* ERROR */
void	ft_error(int err, char *libc);
void	ft_error_exit(int err, char *libc, int status);

/* GARBAGE COLLECTOR */
void	ft_gc(t_shell *shell);
void	ft_gc_cmd(t_shell *shell);
void	ft_gc_2p_str(char **heap);
void	ft_gc_3p_str(char ***heap);

/* SIGNAL */
void	ft_signal(void);
void	ft_sig_int(int sig);
void	ft_signal_default(void);

/* ARGS */
int		ft_argc(char **argv);
char	**ft_argv_dup(char **argv);

/* HEADER */
void	ft_header(void);

/* DEBUG */
void	ft_debug_parser(t_shell *shell);
int		ft_debug_leaks_at_exit(t_shell *shell);

#endif