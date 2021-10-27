#include "minishell.h"

void
	ft_exec(t_shell *shell)
{
	char	**argv;
	int		pid;
	int		wstatus;
	int		wexit;
	int		err;

	int	i;
	i = 0;
	while (shell->cmd[i])
	{
		pid = fork();
		if (pid < 0)
			ft_error_exit(errno, "fork", EXIT_FAILURE);
		if (!pid)
		{
			ft_signal_default();
			argv = ft_argv_dup(shell->cmd[i]);
			/* DEBUG */
			ft_printf("--------------------------------\n");
			ft_printf("DEBUG\n%d\t%s\n", i, argv[0]);
			ft_printf("--------------------------------\n");
			/**/
			if (!ft_exec_is_path(argv[0]))
			{
				if (!ft_exec_env_path(shell, &argv[0]))
					ft_error_exit(ERR_EXEC_NOCMD, NULL, EXIT_FAILURE);
			}
			if (execve(argv[0], argv, shell->env) == -1)
			{
				err = errno;
				rl_clear_history();
				if (err == ENOENT)
					ft_error_exit(ERR_EXEC_NOFILE, NULL, 127);
				if (err == EACCES)
					ft_error_exit(ERR_EXEC_PERM, NULL, 126);
				else
					ft_error_exit(ERR_EXEC_UNKWN, NULL, EXIT_FAILURE);
			}
		}
		else
		{
			wexit = waitpid(pid, &wstatus, WUNTRACED);
			if (wexit == -1)
				ft_error_exit(errno, "waitpid", EXIT_FAILURE);
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
		i++;
	}
}
