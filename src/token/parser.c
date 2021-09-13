#include "minishell.h"

/* TODO : OPERATOR REDIRECTION VALIDITY */
static int	ft_is_valid_line(char *line)
{
	t_token	parser;
	int		i;

	ft_token_init_quotes(&parser);
	i = -1;
	while (line[++i])
	{
		ft_token_quotes(&parser, line[i]);
		if ((parser.s_qts == QTS_CLOSE
				&& parser.d_qts == QTS_CLOSE
				&& ft_is_metachar(line[i]))
			|| (parser.d_qts == QTS_OPEN && line[i] == '\\'
				&& line[i + 1] && line[i + 1] == '\"'))
			return (ERR_SYNTAX_CHAR);
	}
	if (parser.quotes_status == QTS_OPEN)
		return (ERR_SYNTAX_QUOTES);
	return (0);
}

int	ft_parser(char *line_read)
{
	int	err;

	err = ft_is_valid_line(line_read);
	if (err)
		return (ft_perror(err));
	return (1);
}
