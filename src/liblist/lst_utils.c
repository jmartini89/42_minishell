#include "minishell.h"

void
	ft_lstprint(void *content)
{
	ft_printf("%s\n", (char *)content);
}

void
	ft_rdr_print(int type, char *name)
{
	ft_printf("REDIR\ttype\t%d\tname\t%s\n", type, name);
}
