#include "minishell.h"

void
	ft_gc_3p_str(char ***heap)
{
	int	i;
	int	j;

	i = 0;
	while (heap[i])
	{
		j = 0;
		while (heap[i][j])
		{
			free (heap[i][j]);
			j++;
		}
		free (heap[i]);
		i++;
	}
	free (heap);
}

void
	ft_gc_2p_str(char **heap)
{
	int	i;

	i = -1;
	while (heap[++i])
		free (heap[i]);
	free (heap);
}

void
	ft_gc_cmd(char ***heap_c, int *heap_i)
{
	ft_gc_3p_str(heap_c);
	free (heap_i);
}

void
	ft_gc(t_shell *shell)
{
	rl_clear_history();
	ft_gc_2p_str(shell->env);
	free (shell->ret_str);
	shell->ret_str = NULL;
}
