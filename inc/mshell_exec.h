#ifndef MSHELL_EXEC_H
# define MSHELL_EXEC_H

void	ft_exec(t_shell *shell, char **argv);
int		ft_exec_env_path(t_shell *shell, char **arg);

void	ft_test_pipe(t_shell *shell); // DEBUG

#endif