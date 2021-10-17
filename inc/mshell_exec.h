#ifndef MSHELL_EXEC_H
# define MSHELL_EXEC_H

void	ft_exec(t_shell *shell, char **argv);
int		ft_exec_env_path(t_shell *shell, char **arg);

int		ft_builtin_check(t_shell *shell, char **argv);
void	ft_builtin_launch(t_shell *shell, char **argv, int status);

void	ft_test_pipe(t_shell *shell); // DEBUG

#endif