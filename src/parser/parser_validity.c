#include "minishell.h"

static int	ft_is_valid_line(char *line)
{
	int	s_qts;
	int	d_qts;
	int	i;

	i = -1;
	s_qts = 1;
	d_qts = 1;
	while (line[++i])
	{
		if (line[i] == '\"' && s_qts == 1)
			d_qts *= -1;
		if (line[i] == '\'' && d_qts == 1)
			s_qts *= -1;
		if ((s_qts == 1 && d_qts == 1
				&& ft_is_metachar(line[i]))
			|| (d_qts == -1 && line[i] == '\\'
				&& line[i + 1] && line[i + 1] == '\"'))
			return (ERR_SYNTAX_CHAR);
	}
	if (d_qts == -1 || s_qts == -1)
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
