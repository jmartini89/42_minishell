#ifndef MSHELL_SRC_H
# define MSHELL_SRC_H

# define M_SHELL_NAME "miniscell"
# define M_SHELL_PROMPT "\001\e[32m\002"M_SHELL_NAME"\001\e[0m\002$ "

typedef struct s_shell
{
	char	**env;
	char	*cwd;
	char	*ret_str;
	char	***cmd;
	int		*cmd_operator;
}	t_shell;

#endif