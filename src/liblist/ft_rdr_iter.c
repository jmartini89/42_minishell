#include "minishell.h"

void
	ft_rdr_iter(t_redir *lst, void (*f)(int type, char *name))
{
	while (lst)
	{
		(f)(lst->type, lst->name);
		lst = lst->next;
	}
}
