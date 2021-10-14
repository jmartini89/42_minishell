#include "minishell.h"

static void
	fail(const char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}

static void
	do_exec (t_shell *shell, char **argv, int fd_stdin)
{
	char **argv_end;

	for (argv_end = argv; *argv_end && strcmp(*argv_end, "|"); argv_end++)
		;

	int next[2];

	if (pipe(next))
		fail("pipe");

	int pipe_read = next[0];
	int pipe_write = next[1];

	// int bltin = ft_builtin(shell, argv);
	// if (bltin)
	// {
	// 	if (close(pipe_read) == -1)
	// 		fail("close");
	// 	if (close(STDIN_FILENO) == -1)
	// 		fail("close");
	// 	if (dup2(fd_stdin, STDIN_FILENO) == -1)
	// 		fail("dup2");

	// 	ft_builtin_launch(shell, argv, bltin);
	// 	if (*argv_end)
	// 	{
	// 		if (close(STDOUT_FILENO) == -1)
	// 			fail("close");
	// 		if (dup2(pipe_write, STDOUT_FILENO) == -1)
	// 		{
	// 			ft_printf("DEBUG\n");
	// 			fail("dup2");
	// 		}
	// 		do_exec(shell, argv_end + 1, pipe_read);
	// 	}
	// 	else
	// 		return ;
	// }
	pid_t child = fork();

	if (child == -1)
		fail("fork");

	if (!child)
	{
		if (close(pipe_read) == -1)
			fail("close");
		if (close(STDIN_FILENO) == -1)
			fail("close");
		if (dup2(fd_stdin, STDIN_FILENO) == -1)
			fail("dup2");

		if (*argv_end)
		{
			if (close(STDOUT_FILENO) == -1)
				fail("close");
			if (dup2(pipe_write, STDOUT_FILENO) == -1)
				fail("dup2");
		}

		*argv_end = NULL;
		if (execvp(argv[0], argv) == -1)
			fail("execvp");
	}
	else
	{
		if (close(pipe_write) == -1)
			fail("close");

		if (*argv_end)
			do_exec(shell, argv_end + 1, pipe_read);

		if (waitpid(child, NULL, 0) == -1)
			fail("wait");
	}
}

void
	ft_test_pipe(t_shell *shell)
{
	char **argv;

	argv = shell->token;

	if (ft_argc(argv) <= 1)
		return ;

	do_exec(shell, argv, dup(STDIN_FILENO));
}
