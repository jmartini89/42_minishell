#include "minishell.h"

void
	ft_rdr_add_back(t_redir **lst, t_redir *new)
{
	t_redir	*ptr;

	ptr = NULL;
	if (*lst)
	{
		ptr = ft_rdr_last(*lst);
		ptr->next = new;
	}
	else
		*lst = new;
}
