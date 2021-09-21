#ifndef MSHELL_MAIN_H
# define MSHELL_MAIN_H

# define M_SHELL_NAME "miniscell"

typedef struct s_shell
{
	char	**env;
	char	*cwd;
}	t_shell;

#endif