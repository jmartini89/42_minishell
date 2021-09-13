#include "minishell.h"

static void	ft_env_test(char *line)
{
	char	*env_test;

	env_test = getenv(line);
	if (env_test)
		ft_printf("ENV TEST : %s\n", env_test);
}

int	ft_parser(char *line_read)
{
	if (!ft_validity_check(line_read))
		return (0);
	ft_token(line_read);
	return (1);
}
