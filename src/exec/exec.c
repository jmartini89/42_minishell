#include "minishell.h"

void
	ft_exec(t_shell *shell)
{
	char	**argv;
	int		builtin;
	int		pid;
	int		wstatus;
	int		wexit;
	int		err;
	int		i;

	/* PIPE TEST */
	if (!ft_memcmp(shell->cmd[0][0], "pipe", 4) && ft_strlen(shell->cmd[0][0]) == 4)
	{
		ft_test_pipe(shell);
		return ;
	}
	/**/
	builtin = ft_builtin_check(shell, shell->cmd[0]);
	if (shell->cmd_cnt == 1 && builtin)
	{
		ft_builtin_launch(shell, shell->cmd[0], builtin, 0);
		return ;
	}
	i = 0;
	while (shell->cmd[i])
	{
		if (!shell->cmd_operator[i])
		{
			if (i && shell->cmd_operator[i - 1])
				ft_printf("***\tPIPE L TODO\n");
			if (shell->cmd[i + 1] && shell->cmd_operator[i + 1])
				ft_printf("***\tPIPE R TODO\n");
			pid = fork();
			if (pid < 0)
				ft_error_exit(errno, "fork", EXIT_FAILURE);
			if (!pid)
			{
				ft_signal_default();
				builtin = ft_builtin_check(shell, shell->cmd[i]);
				if (builtin)
					ft_builtin_launch(shell, shell->cmd[i], builtin, 1);
				else if (!ft_exec_is_path(shell->cmd[i][0]))
					if (!ft_exec_env_path(shell, &shell->cmd[i][0]))
						ft_error_exit(ERR_EXEC_NOCMD, NULL, 127);
				if (execve(shell->cmd[i][0], shell->cmd[i], shell->env) == -1)
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
