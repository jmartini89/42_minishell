#include "minishell.h"

void
	ft_redir(t_redir *redir)
{
	int		fd_write;
	int		fd_read;
	int		tmp;
	void	*next;

	if (redir == NULL)
		return ;
	next = redir;
	while (next)
	{
		ft_printf("%d %s", redir->type, redir->name);
		next = redir->next;
	}
}
