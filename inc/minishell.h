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
# include <sys/stat.h>
# include <dirent.h>
# include <signal.h>
# include <fcntl.h>

/* LOCAL LIBRARIES*/
# include "libft.h"
# include "ft_printf.h"

/* SUB_HEADERS */
# include "mshell_src.h"
# include "mshell_utils.h"
# include "mshell_env.h"
# include "mshell_parser.h"
# include "mshell_builtin.h"
# include "mshell_exec.h"

#endif