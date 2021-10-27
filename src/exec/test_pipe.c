#include "minishell.h"

void
	ft_test_pipe(t_shell *shell)
{
	// int		pipefd[2];
	// pid_t	pid;
	// char	**arg1;
	// char	**arg2;

	// arg1 = calloc(3, sizeof(*arg1));
	// arg1[0] = "/bin/grep";
	// arg1[1] = "e";
	// arg2 = calloc(3, sizeof(*arg2));
	// arg2[0] = "echo";
	// arg2[1] = "test";
	// int stdout_cpy;
	// printf("FD NOT INITIALISED\t%d\n", stdout_cpy);
	// pipe(pipefd);
	// pid = fork();
	// if (!pid)
	// {
	// 	close (pipefd[0]);
	// 	close (pipefd[1]);
	// 	dup2(pipefd[0], STDIN_FILENO);
	// 	close (pipefd[0]);
	// 	close (pipefd[1]);
	// 	close (stdout_cpy);
	// 	if (execve(arg1[0], arg1, shell->env) < 0)
	// 		printf("EXECVE ERROR\n");
	// }
	// else
	// {
	// 	if (write(1, "ciao\n", 6) == -1)
	// 		ft_perrno(errno, "write");
	// 	dup2(pipefd[1], STDOUT_FILENO);
	// 	ft_echo(shell, arg2, 0);
	// 	close (pipefd[0]);
	// 	close (pipefd[1]);
	// 	dup2(stdout_cpy, STDOUT_FILENO);
	// 	close (stdout_cpy);
	// 	waitpid(pid, NULL, WUNTRACED);
	// }
	// if (waitpid(pid, NULL, 0) == -1)
	// 	perror("wait");
	// close (pipefd[0]);
	// close (pipefd[1]);
	// free (arg1);
	// free (arg2);

	int fd;
	fd = open("test.txt", O_CREAT | O_TRUNC | O_RDWR,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd < 0)
		ft_printf("ERROR\n");
	char *buf = "ciaodashello";
	write(fd, buf, ft_strlen(buf));
	close (fd);
}
