#ifndef M_SHELL_BUILTIN_H
# define M_SHELL_BUILTIN_H

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

int	ft_builtin(t_shell *shell, char **arg);
int	ft_export(t_shell *shell, char **argv);

#endif