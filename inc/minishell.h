#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_def.h"
# include "minishell_parser.h"
# include "libft.h"
# include "ft_printf.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

/* UTILS */
int	ft_perror(int err);
int	ft_is_space_tab(char c);

#endif