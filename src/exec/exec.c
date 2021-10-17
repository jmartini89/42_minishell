#include "minishell.h"

static int
	ft_exec_is_path(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void
	ft_exec(t_shell *shell, char **argv)
{
	char	**argv_heap;
	int		pid;
	int		wstatus;
	int		wexit;
	int		err;

	argv_heap = ft_argv_dup(argv);
	if (!ft_exec_is_path(argv_heap[0]))
	{
		if (!ft_exec_env_path(shell, &argv_heap[0]))
		{
			ft_gc_arr_str(argv_heap);
			ft_perrno(ERR_EXEC_NOCMD, NULL);
			ft_env_return(shell, 1);
			return ;
		}
	}
	pid = fork();
	if (pid < 0)
		ft_perrno_exit(ERR_SYS_FORK, EXIT_FAILURE);
	if (!pid)
	{
		ft_signal_default();
		if (execve(argv_heap[0], argv_heap, shell->env) < 0)
		{
			err = errno;
			rl_clear_history();
			if (err == ENOENT)
				ft_perrno_exit(ERR_EXEC_NOFILE, 127);
			if (err == EACCES)
				ft_perrno_exit(ERR_EXEC_PERM, 126);
			else
				ft_perrno_exit(ERR_EXEC_UNKWN, EXIT_FAILURE);
		}
	}
	else
	{
		wexit = waitpid(-1, &wstatus, WUNTRACED);
		if (wexit < 0)
			ft_perrno_exit(ERR_SYS_FORK, EXIT_FAILURE);
		if (WIFSTOPPED(wstatus))
			ft_env_return(shell, WSTOPSIG(wstatus) + 128);
		if (WIFSIGNALED(wstatus))
		{
			ft_printf("\n");
			ft_env_return(shell, WTERMSIG(wstatus) + 128);
		}
		if (WIFEXITED(wstatus))
			ft_env_return(shell, WEXITSTATUS(wstatus));
	}
	ft_gc_arr_str(argv_heap);
}