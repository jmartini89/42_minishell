#ifndef MSHELL_UTILS_H
# define MSHELL_UTILS_H

/* FT_PERROR */
int		ft_perror(int err);
enum	e_err {
	ERR_UNDEF,
	ERR_SYS_MALLOC,
	ERR_SYNTAX_QUOTES,
	ERR_SYNTAX_CHAR,
	ERR_SYNTAX_TKN,
};
static const char *const	g_errstr[] = {
	"Undefined",
	"System : malloc fail",
	"Syntax : unclosed quotes",
	"Syntax : undefined special character",
	"Syntax : unexpected token",
};

/* UTILS */

void	ft_signal(void);
void	ft_sig_void(int sig);
void	ft_gc(t_shell *shell);

#endif