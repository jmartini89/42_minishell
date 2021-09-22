#ifndef MSHELL_ENV_H
# define MSHELL_ENV_H

int		ft_env_init(t_shell *shell, char **envp);
char	*ft_getenv(t_shell *shell, char *str);

#endif