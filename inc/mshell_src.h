#ifndef MSHELL_SRC_H
# define MSHELL_SRC_H

# define M_SHELL_NAME "miniscell"
# define M_SHELL_PROMPT "\e[32m"M_SHELL_NAME"\e[0m$ "

typedef struct s_shell
{
	char	**env;
	char	*cwd;
	char	**token;
	int		*tkn_literal;
	int		literal;
	char	*ret_str;
}	t_shell;

#endif