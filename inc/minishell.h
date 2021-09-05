#ifndef MINISHELL_H
# define MINISHELL_H
# include "minishell_def.h"
# include "../lib/libft/libft.h"
# include "../lib/libftprintf/ft_printf.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

int	ft_parser(char *line_read);
int	ft_perror(int err);

#endif