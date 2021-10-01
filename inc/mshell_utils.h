#ifndef MSHELL_UTILS_H
# define MSHELL_UTILS_H

enum	e_err {
	ERR_UNDEF,
	ERR_SYS_MALLOC,
	ERR_SYS_FORK,
	ERR_SYNTAX_QUOTES,
	ERR_SYNTAX_CHAR,
	ERR_SYNTAX_TKN,
	ERR_BLTIN_ENV,
	ERR_EXEC_NOFILE,
};
static const char *const	g_errstr[] = {
	"Undefined",
	"*** SYSTEM ERROR : MALLOC FAIL ***",
	"*** SYSTEM ERROR : FORK FAIL ***",
	"syntax error : unclosed quotes",
	"syntax error : undefined special character",
	"syntax error : unexpected token",
	"builtin : env : arguments are not supported",
	"execve error : no such file or directory",
};

int		ft_perror(int err);
void	ft_perror_exit(int err);
void	ft_signal(void);
void	ft_sig_void(int sig);

#endif