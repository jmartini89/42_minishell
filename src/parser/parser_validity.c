#include "minishell.h"

static int	ft_is_valid_line(char *line)
{
	int	single_quotes;
	int	double_quotes;
	int	i;

	i = -1;
	single_quotes = 1;
	double_quotes = 1;
	while (line[++i])
	{
		if (line[i] == '\"' && single_quotes == 1)
			double_quotes *= -1;
		if (line[i] == '\'' && double_quotes == 1)
			single_quotes *= -1;
		if ((single_quotes == 1 && double_quotes == 1
				&& ft_is_metachar(line[i]))
			|| (double_quotes == -1 && line[i] == '\\'
				&& line[i + 1] && line[i + 1] == '\"'))
			return (ERR_SYNTAX_CHAR);
	}
	if (double_quotes == -1 || single_quotes == -1)
		return (ERR_SYNTAX_QUOTES);
	return (0);
}

int	ft_validity_check(char *line_read)
{
	int	err;

	err = ft_is_valid_line(line_read);
	if (err)
		return (ft_perror(err));
	return (1);
}