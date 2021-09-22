#ifndef MSHELL_SRC_H
# define MSHELL_SRC_H

# define M_SHELL_NAME "miniscell"

typedef struct s_shell
{
	char	**env;
	char	*cwd;
	char	**token;
	int		*tkn_operators;
}	t_shell;

#endif