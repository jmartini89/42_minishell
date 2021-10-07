#include "minishell.h"

static int	ft_exec_is_path(char *arg)
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

void	ft_exec(t_shell *shell, char **argv)
{
	char	**argv_heap;
	int		pid;
	int		wstatus;
	int		wexit;
	int		err;

	argv_heap = ft_argv_dup(argv);
	if (!ft_exec_is_path(argv_heap[0]))
		ft_exec_env_path(shell, &argv_heap[0]);
	pid = fork();
	if (pid < 0)
		ft_perrno_exit(ERR_SYS_FORK);
	if (!pid)
	{
		ft_signal_dfl();
		if (execve(argv_heap[0], argv_heap, shell->env) < 0)
		{
			err = errno;
			rl_clear_history();
			ft_perrno(ERR_EXEC_NOFILE, NULL); // GENERIC
			ft_printf("ERRNO %d\n", err);
			if (err == ENOENT)
				exit (127);
			if (err == EPERM)
				exit (126);
			else // TODO : PROPER EXIT
				exit (err);
		}
	}
	else
	{
		//signal(SIGINT, SIG_IGN);
		wexit = wait(&wstatus);
		if (wexit < 0)
			ft_perrno_exit(ERR_SYS_FORK);
		if (WIFSIGNALED(wstatus))
		{
			ft_printf("\n");
			ft_env_return(shell, WTERMSIG(wstatus) + 128);
			//ft_printf("EXIT STATUS\t%s\n", shell->ret_str);
		}
		if (WEXITSTATUS(wstatus))
		{
			ft_env_return(shell, WEXITSTATUS(wstatus));
			//ft_printf("EXIT STATUS\t%s\n", shell->ret_str);
		}
	}
	ft_gc_arr_str(argv_heap);
}
