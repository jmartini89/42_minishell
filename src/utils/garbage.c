#include "minishell.h"

void
	ft_gc_cmd(char ***cmd) // WIP
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			free (cmd[i][j]);
			j++;
		}
		free (cmd[i]);
		i++;
	}
	free (cmd);
	cmd = NULL;
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
