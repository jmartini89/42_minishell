#ifndef MSHELL_MAIN_H
# define MSHELL_MAIN_H

# define M_SHELL_NAME "miniscell"

typedef struct s_shell
{
	char	**env;
	char	*cwd;
}	t_shell;

void	ft_signal(void);
void	ft_sig_void(int sig);
void	ft_gc(t_shell *shell);

#endif