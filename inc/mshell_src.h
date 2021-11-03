#ifndef MSHELL_SRC_H
# define MSHELL_SRC_H

# define M_SHELL_NAME "miniscell"
# define M_SHELL_PROMPT "\001\e[32m\002"M_SHELL_NAME"\001\e[0m\002$ "

typedef struct s_redir
{
	int		type;
	char	*name;
	void	*next;
}	t_redir;

typedef struct s_cmd
{
	char	**argv;
	t_redir	*redir;
	int		pipe_r;
	int		pipe_w;
}	t_cmd;

typedef struct s_shell
{
	char	**env;
	char	*cwd;
	char	*ret_str;
	char	***cmd;			// OBSOLETE
	int		*cmd_operator;	// OBSOLETE
	t_cmd	*cmd_arr;
	int		cmd_cnt;
}	t_shell;

#endif