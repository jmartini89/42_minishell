#ifndef MSHELL_EXEC_H
# define MSHELL_EXEC_H

enum	e_builtin {
	BLTIN_EXEC,
	BLTIN_CD,
	BLTIN_ECHO,
	BLTIN_ENV,
	BLTIN_EXIT,
	BLTIN_EXPORT,
	BLTIN_PWD,
	BLTIN_UNSET,
};

void	ft_exec(t_shell *shell);
int		ft_exec_is_path(char *arg);
int		ft_exec_env_path(t_shell *shell, char **arg);

int		ft_builtin_check(t_shell *shell, char **argv);
void	ft_builtin_launch(
			t_shell *shell, char **argv, int status, int process);

void	ft_test_pipe(t_shell *shell); // DEBUG

#endif