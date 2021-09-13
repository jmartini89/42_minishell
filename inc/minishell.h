#ifndef MINISHELL_H
# define MINISHELL_H
/* PROJECT */
# include "minishell_err.h"
# include "minishell_utils.h"
# include "minishell_parser.h"
/* LOCAL LIBRARIES*/
# include "libft.h"
# include "ft_printf.h"
/* SYS LIBRARIES */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define M_SHELL_NAME "miniscell"

#endif