#include "minishell.h"

static void	ft_env_test(char *line)
{
	char	*env_test;

	env_test = getenv(line);
	if (env_test)
		ft_printf("ENV TEST : %s\n", env_test);
}

/*
** TODO : implement translation layers :
** * QUOTES
** * DOLLAR
*/
static	char	**ft_token_assembler(char *start, char *end)
{
	char	*output;
	int		len;

	len = end - start + 1;
	output = ft_calloc(len + 1, sizeof(*output));
	ft_memcpy(output, start, len);
	ft_printf("ARGS_ASSEMBLER : %s\n", output);
	ft_env_test(output);
	free (output);
	return (NULL);
}

static void	ft_quotes_def(t_token *tkn, char *c)
{
	if (*c == '\"' && tkn->single_quotes == 1)
		tkn->double_quotes *= -1;
	if (*c == '\'' && tkn->double_quotes == 1)
		tkn->single_quotes *= -1;
	if (tkn->single_quotes == -1 || tkn->double_quotes == -1)
		tkn->quotes_status = -1;
	else
		tkn->quotes_status = 1;
}

/* OPERATOR TO BE IMPLEMENTED PROPERLY */
static void	ft_token_find(t_token *tkn, char *c)
{
	if (ft_is_operator(*c) && !tkn->start)
	{
		tkn->start = c;
		tkn->end = c;
	}
	if (!ft_is_space_tab(*c) && !tkn->start)
		tkn->start = c;
	if (ft_is_operator(*(c + 1))
		&& tkn->start && !tkn->end && tkn->quotes_status == 1)
		tkn->end = c;
	if (ft_is_space_tab(*c)
		&& tkn->start && !tkn->end && tkn->quotes_status == 1)
		tkn->end = c - 1;
	if (*(c + 1) == '\0' && !ft_is_space_tab(*c))
		tkn->end = c;
}

void	ft_token(char *line)
{
	t_token	tkn;
	int		i;

	tkn.start = NULL;
	tkn.end = NULL;
	tkn.single_quotes = 1;
	tkn.double_quotes = 1;
	tkn.quotes_status = 1;
	i = -1;
	while (line[++i])
	{
		ft_quotes_def(&tkn, &line[i]);
		ft_token_find(&tkn, &line[i]);
		if (tkn.end)
		{
			ft_token_assembler(tkn.start, tkn.end);
			tkn.start = NULL;
			tkn.end = NULL;
		}
	}
}
