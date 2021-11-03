#include "minishell.h"

t_redir
	*ft_rdr_new(int type, char *name)
{
	t_redir	*new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	new->type = type;
	new->name = name;
	new->next = NULL;
	return (new);
}
