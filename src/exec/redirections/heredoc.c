#include "minishell.h"

/*
		NEW LAUNCH LOGIC - REWRITE NEEDED
*/

int
	ft_heredoc(t_redir *lst)
{
	char	*line;
	int		fd;
	int		len;

	fd = open(TMPFILE, O_CREAT |  O_TRUNC | O_APPEND | O_RDWR,
				S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH);
	if (fd == -1)
	{
		ft_error(errno, "open");
		return (0);
	}
	len = ft_strlen(lst->name);
	while (1)
	{
		line = NULL;
		line = readline("> ");
		if (line == NULL)
		{
			ft_error(WRN_HEREDOC, NULL);
			if (close(fd) == -1)
				ft_error_exit(errno, "close", EXIT_FAILURE);
			return (0);
		}
		if (line && *line)
		{
			if (ft_strlen(line) == len && !ft_memcmp(lst->name, line, len))
			{
				free (line);
				if (close(fd) == -1)
					ft_error_exit(errno, "close", EXIT_FAILURE);
				return (1);
			}
			write(fd, line, ft_strlen(line));
			write(fd, "\n", 1);
			free (line);
		}
	}
}
