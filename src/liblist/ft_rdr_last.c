#include "minishell.h"

t_redir
	*ft_rdr_last(t_redir *lst)
{
	t_redir	*ptr;

	ptr = NULL;
	if (lst)
	{
		ptr = lst;
		while (ptr->next)
			ptr = ptr->next;
	}
	return (ptr);
}
