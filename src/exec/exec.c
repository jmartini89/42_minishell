#include "minishell.h"

void
	ft_exec(t_shell *shell)
{
	int		builtin;
	int		pid;
	// int		*pid_arr;
	int		wstatus;
	int		wexit;
	int		err;
	int		i;

	builtin = ft_builtin_check(shell->cmd[0].argv);
	if (shell->cmd_cnt == 1 && builtin)
	{
		if (shell->cmd[0].redir)
			ft_printf("EXEC REDIRECTION DEBUG\n");
		ft_builtin_launch(shell, shell->cmd[0].argv, builtin, FALSE);
		return ;
	}

	i = 0;
	while (i < shell->cmd_cnt)
	{
		if (shell->cmd[i].argv)
		{
			pid = fork();
			if (pid < 0)
				ft_error_exit(errno, "fork", EXIT_FAILURE);
			if (!pid)
			{
				ft_signal_default();
				builtin = ft_builtin_check(shell->cmd[i].argv);
				if (builtin)
					ft_builtin_launch(shell, shell->cmd[i].argv, builtin, TRUE);
				else if (!ft_is_path(shell->cmd[i].argv[0]))
					if (!ft_exec_env_path(shell, &shell->cmd[i].argv[0]))
						ft_error_exit(ERR_EXEC_NOCMD, NULL, 127);
				if (execve(shell->cmd[i].argv[0], shell->cmd[i].argv, shell->env) == -1)
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
		}
		i++;
	}
}
