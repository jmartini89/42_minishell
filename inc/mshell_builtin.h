#ifndef MSHELL_BUILTIN_H
# define MSHELL_BUILTIN_H

/* BUILT-IN */
void	ft_builtin(t_shell *shell, char **argv);
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

void	ft_test_pipe(t_shell *shell); // DEBUG

#endif