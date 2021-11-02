#include "minishell.h"

static int
	ft_is_valid_operator(t_token *parser, char *c)
{
	int	operator;

	operator = ft_is_operator(*c);
	if (operator == PIPE)
	{
		if (*(c + 1)
			&& ft_is_operator(*(c + 1)) == operator)
			return (0);
	}
	if (operator == R_OUT || operator == R_IN)
	{
		if (*(c + 1) && *(c + 2)
			&& ft_is_operator(*(c + 1)) == operator
			&& ft_is_operator(*(c + 2)) == operator)
			return (0);
	}
	return (1);
}

static int
	ft_is_valid_line(char *line)
{
	t_token	parser;
	int		i;

	ft_token_init_quotes(&parser);
	i = -1;
	while (line[++i])
	{
		ft_token_quotes_status(&parser, line[i]);
		if (ft_is_metachar(line[i])
			&& parser.quotes_status == QTS_CLOSE)
			return (ERR_SYNTAX_CHAR);
		if (ft_is_operator(line[i])
			&& parser.quotes_status == QTS_CLOSE
			&& !ft_is_valid_operator(&parser, &line[i]))
			return (ERR_SYNTAX_TKN);
	}
	if (parser.quotes_status == QTS_OPEN)
		return (ERR_SYNTAX_QUOTES);
	return (0);
}

int
	ft_token_syntax(char *line_read, t_shell *shell)
{
	int	err;

	err = ft_is_valid_line(line_read);
	if (err)
	{
		ft_error(err, NULL);
		ft_env_return(shell, 2);
		return (0);
	}
	return (1);
}
