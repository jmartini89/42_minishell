#include "minishell.h"

void
	ft_gc_token(char **token, int *literal)
{
	int	i;

	i = -1;
	while (token[++i])
		free (token[i]);
	free (token);
	free (literal);
	token = NULL;
}

void
	ft_gc_arr_str(char **heap)
{
	int	i;

	i = -1;
	while (heap[++i])
		free (heap[i]);
	free (heap);
	heap = NULL;
}

void
	ft_gc(t_shell *shell)
{
	rl_clear_history();
	ft_gc_arr_str(shell->env);
	free (shell->ret_str);
}
