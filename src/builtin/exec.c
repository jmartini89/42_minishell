#include "minishell.h"

void	ft_exec(t_shell *shell, char **argv)
{
	int				pid;
	int				wstatus;
	int				wexit;
	int				err;
	DIR				*dir;
	struct dirent	*dirent;

	/*
	dir = opendir("/bin");
	while (dirent = readdir(dir))
		ft_printf("%s\n", dirent->d_name);
	closedir(dir);
	*/
	pid = fork();
	if (pid < 0)
		ft_perror_exit(ERR_SYS_FORK);
	if (!pid)
	{
		if (execve(argv[0], argv, shell->env) < 0)
		{
			err = errno;
			free (shell->line_read);
			shell->line_read = NULL;
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
}
