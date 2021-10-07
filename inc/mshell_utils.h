#ifndef MSHELL_UTILS_H
# define MSHELL_UTILS_H

enum	e_err {
	ERR_UNDEF,
	ERR_SYS_MALLOC,
	ERR_SYS_FORK,
	ERR_SYNTAX_QUOTES,
	ERR_SYNTAX_CHAR,
	ERR_SYNTAX_TKN,
	ERR_BLTIN_ARGS,
	ERR_BLTIN_CD_ARGS,
	ERR_BLTIN_CD_HOME,
	ERR_BLTIN_PWD_NDIR,
	ERR_BLTIN_UNSET,
	ERR_EXEC_NOFILE,
	ERR_EXEC_NOCMD,
};
static const char *const	g_errstr[] = {
	"Undefined",
	"*** SYSTEM ERROR : MALLOC FAIL ***",
	"*** SYSTEM ERROR : FORK FAIL ***",
	"syntax error: unclosed quotes",
	"syntax error: undefined special character",
	"syntax error: unexpected token",
	"built-in: arguments are not supported",
	"cd: too many arguments",
	"cd: HOME not set",
	"pwd: the current working directory has been unlinked",
	"unset: not a valid identifier",
	"execve: no such file or directory",
	"execve: command not found",
};

/* ERROR */
void	ft_perrno(int err, char *libc);
void	ft_perrno_exit(int err);

/* GARBAGE COLLECTOR */
void	ft_gc(t_shell *shell);
void	ft_gc_arr_str(char **heap);
void	ft_gc_token(char **token, int *literal);

/* SIGNAL */
void	ft_signal(void);
void	ft_sig_int(int sig);
void	ft_signal_dfl(void);

/* ARGS */
int		ft_argc(char **argv);
char	**ft_argv_dup(char **argv);

#endif