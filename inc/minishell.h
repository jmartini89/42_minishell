#ifndef MINISHELL_H
# define MINISHELL_H
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
/* LOCAL LIBRARIES*/
# include "libft.h"
# include "ft_printf.h"
/* SUB_HEADERS */
# include "mshell_src.h"
# include "mshell_utils.h"
# include "mshell_env.h"
# include "mshell_token.h"
# include "mshell_builtin.h"
# include "mshell_gc.h"

#endif