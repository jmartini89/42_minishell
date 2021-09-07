#include "minishell.h"

static	char	**ft_args_assembler(char *start, char *end)
{
	char	*output;
	int		len;

	len = end - start + 1;
	output = ft_calloc(len + 1, sizeof(*output));
	ft_memcpy(output, start, len);
	ft_printf("ARGS_ASSEMBLER : %s\n", output);
	/*
	char	*env_test;
	env_test = getenv(output);
	if (env_test)
		ft_printf("%s\n", env_test);
	*/
	free (output);
	return (NULL);
}

static	void	ft_args_finder(char *line_read)
{
	char	**parsed;
	char	*arg_start;
	char	*arg_end;
	int		single_quotes;
	int		double_quotes;
	int		quotes_status;
	int		i;

	arg_start = NULL;
	arg_end = NULL;
	single_quotes = 1;
	double_quotes = 1;
	quotes_status = 1;
	i = -1;
	//	QUOTES	DOLLAR	PIPE
	while (line_read[++i]) // read until arg_end then assemble
	{
		if (!ft_is_space_tab(line_read[i]) && !arg_start)
		{
			// if quotes start -> i++ && update quotes
			arg_start = &line_read[i];
		}
		/* ! if quotes end ! */
		if (ft_is_space_tab(line_read[i]) && arg_start && !arg_end && quotes_status)
			arg_end = &line_read[i - 1];
		if (line_read[i + 1] == '\0' && !ft_is_space_tab(line_read[i]))
			arg_end = &line_read[i];
		if (arg_end)
		{
			ft_args_assembler(arg_start, arg_end);
			arg_start = NULL;
			arg_end = NULL;
		}
	}
}

int	ft_parser(char *line_read)
{
	if (!ft_validity_check(line_read))
		return (0);
	ft_args_finder(line_read);
	return (1);
}
