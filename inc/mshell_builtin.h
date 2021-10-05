#ifndef M_SHELL_BUILTIN_H
# define M_SHELL_BUILTIN_H

void	ft_builtin(t_shell *shell, char **argv);
void	ft_chdir(t_shell *shell, char **argv);
void	ft_echo(t_shell *shell, char **argv);
void	ft_env(t_shell *shell, char **argv);
void	ft_exec(t_shell *shell, char **argv);
void	ft_exit(t_shell *shell, char **argv);
void	ft_export(t_shell *shell, char **argv);
void	ft_pwd(t_shell *shell, char **argv);
void	ft_unset(t_shell *shell, char **argv);

#endif