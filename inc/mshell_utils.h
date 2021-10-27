#ifndef MSHELL_UTILS_H
# define MSHELL_UTILS_H

enum	e_err {
	ERR_UNDEF,
	ERR_SYNTAX_QUOTES,
	ERR_SYNTAX_CHAR,
	ERR_SYNTAX_TKN,
	ERR_BLTIN_ARGS,
	ERR_BLTIN_CD_ARGS,
	ERR_BLTIN_CD_HOME,
	ERR_BLTIN_EXPORT,
	ERR_BLTIN_PWD_NDIR,
	ERR_BLTIN_UNSET,
	ERR_EXEC_NOFILE,
	ERR_EXEC_PERM,
	ERR_EXEC_NOCMD,
	ERR_EXEC_UNKWN,
};
static const char *const	g_errstr[] = {
	"Undefined",
	"syntax error: unclosed quotes",
	"syntax error: undefined special character",
	"syntax error: unexpected token",
	"built-in: arguments are not supported",
	"cd: too many arguments",
	"cd: HOME not set",
	"export: not a valid identifier",
	"pwd: the current working directory has been unlinked",
	"unset: not a valid identifier",
	"execve: no such file or directory",
	"execve: permission denied",
	"execve: command not found",
	"execve: unknown error",
};

/* ERROR */
void	ft_error(int err, char *libc);
void	ft_error_exit(int err, char *libc, int status);

/* GARBAGE COLLECTOR */
void	ft_gc(t_shell *shell);
void	ft_gc_arr_str(char **heap);
void	ft_gc_cmd(char ***cmd, int *cmd_operator);

/* SIGNAL */
void	ft_signal(void);
void	ft_sig_int(int sig);
void	ft_signal_default(void);

/* ARGS */
int		ft_argc(char **argv);
char	**ft_argv_dup(char **argv);

#endif