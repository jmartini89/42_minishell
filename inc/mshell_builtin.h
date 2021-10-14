#ifndef MSHELL_BUILTIN_H
# define MSHELL_BUILTIN_H

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

/* BUILT-IN */
int		ft_builtin(t_shell *shell, char **argv);
void	ft_builtin_launch(t_shell *shell, char **argv, int status);
void	ft_cd(t_shell *shell, char **argv);
void	ft_echo(t_shell *shell, char **argv);
void	ft_env(t_shell *shell, char **argv);
void	ft_exit(t_shell *shell, char **argv);
void	ft_export(t_shell *shell, char **argv);
void	ft_pwd(t_shell *shell, char **argv);
void	ft_unset(t_shell *shell, char **argv);

/* EXEC */
void	ft_exec(t_shell *shell, char **argv);
int		ft_exec_env_path(t_shell *shell, char **arg);

/* UTILS */
char	*ft_getcwd(t_shell *shell);
void	ft_pwd_export_old(t_shell *shell);
void	ft_pwd_export_new(t_shell *shell);

// TEST
void	ft_test_pipe(t_shell *shell); // DEBUG

#endif