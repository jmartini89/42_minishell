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
};
static const char *const	g_errstr[] = {
	"Undefined",
	"*** SYSTEM ERROR : MALLOC FAIL ***",
	"*** SYSTEM ERROR : FORK FAIL ***",
	"syntax error : unclosed quotes",
	"syntax error : undefined special character",
	"syntax error : unexpected token",
	"built-in error : arguments are not supported",
	"cd error : too many arguments",
	"cd error : HOME not set",
	"pwd error : the current working directory has been unlinked",
	"unset error : not a valid identifier",
	"execve error : no such file or directory",
};

/* ERROR */
int		ft_perror(int err);
void	ft_perror_exit(int err);
int		ft_strerror(char *type, int err);

/* GARBAGE COLLECTOR */
void	ft_gc(t_shell *shell);
void	ft_gc_arr_str(char **heap);
void	ft_gc_token(char **token, int *literal);

/* SIGNAL */
void	ft_signal(void);
void	ft_sig_int(int sig);

/* ARGS */
int		ft_argc(char **argv);
char	**ft_argv_dup(char **argv);

#endif