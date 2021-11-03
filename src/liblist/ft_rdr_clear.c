#include "minishell.h"

void
	ft_rdr_clear(t_redir **lst, void (*del)(void *))
{
	t_redir	*ptr;
	t_redir	*tmp;

	if (*lst)
	{
		ptr = *lst;
		while (ptr)
		{
			tmp = ptr;
			(del)(ptr->name);
			ptr = ptr->next;
			free(tmp);
		}
	}
	*lst = NULL;
}
