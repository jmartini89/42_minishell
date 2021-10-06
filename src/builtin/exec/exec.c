#include "minishell.h"

static char	**ft_argv_dup(char **argv)
{
	char	**heap;
	int		len;

	len = ft_argc(argv);
	heap = ft_calloc(len + 1, sizeof(*heap));
	if (!heap)
		ft_perror_exit(ERR_SYS_MALLOC);
	len = -1;
	while (argv[++len])
	{
		heap[len] = ft_strdup(argv[len]);
		if (!heap[len])
			ft_perror_exit(ERR_SYS_MALLOC);
	}
	return (heap);
}

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
		ft_perror_exit(ERR_SYS_FORK);
	if (!pid)
	{
		if (execve(argv_heap[0], argv_heap, shell->env) < 0)
		{
			err = errno;
			ft_perror(ERR_EXEC_NOFILE); // GENERIC
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
		signal(SIGINT, ft_sig_void);
		wexit = wait(&wstatus);
		if (wexit < 0)
			ft_perror_exit(ERR_SYS_FORK);
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
