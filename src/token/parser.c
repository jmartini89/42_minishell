#include "minishell.h"

/* TODO : OPERATOR REDIRECTION VALIDITY */
static int	ft_is_valid_line(char *line)
{
	t_token	tkn_valid;
	int		i;

	ft_token_init_quotes(&tkn_valid);
	i = -1;
	while (line[++i])
	{
		ft_token_quotes(&tkn_valid, line[i]);
		if ((tkn_valid.s_qts == QTS_CLOSE
				&& tkn_valid.d_qts == QTS_CLOSE
				&& ft_is_metachar(line[i]))
			|| (tkn_valid.d_qts == QTS_OPEN && line[i] == '\\'
				&& line[i + 1] && line[i + 1] == '\"'))
			return (ERR_SYNTAX_CHAR);
	}
	if (tkn_valid.quotes_status == QTS_OPEN)
		return (ERR_SYNTAX_QUOTES);
	return (0);
}

static int	ft_parser_validity(char *line_read)
{
	int	err;

	err = ft_is_valid_line(line_read);
	if (err)
		return (ft_perror(err));
	return (1);
}

int	ft_parser(char *line_read)
{
	if (!ft_parser_validity(line_read))
		return (0);
	return (1);
}
