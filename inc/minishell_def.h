#ifndef MINISHELL_DEF_H
# define MINISHELL_DEF_H
# define M_SHELL_NAME "miniscell"

enum	e_err {
	ERR_UNDEF,
	ERR_SYNTAX_QUOTES,
	ERR_SYNTAX_CHAR,
};
static const char *const	g_errstr[] = {
	"Undefined",
	"Syntax : unclosed quotes",
	"Syntax : undefined special character",
};

#endif