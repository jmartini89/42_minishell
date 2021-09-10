#include "minishell.h"

static	char	*ft_first_traduction(char *arg)
{
	int		i;
	int		j;
	int		cnt;
	int		len;
	char	*tmp;

	cnt = 0;
	j = 0;
	i = - 1;
	while (arg[++i])
	{
		if(arg[i] == '\'' || arg[i] == '\"')
			cnt++;
	}
	len = ft_strlen(arg) - cnt;
	tmp = ft_calloc(len + 1, sizeof(*tmp));
	i = - 1;
	while (arg[++i])
	{
		if(arg[i] != '\'' && arg[i] != '\"')
		{
			tmp[j] = arg[i];
			j++;
		}
	}
	ft_printf("tmp : %s\n", tmp);
	ft_printf("arg : %s\n", arg);
	arg = tmp;
	ft_printf("tmp2: %s\n", tmp);
	ft_printf("arg2: %s\n", arg);
	return(arg);
}


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
static	char	**ft_args_assembler(char *start, char *end)
{
	char	*output;
	int		len;

	len = end - start + 1;
	output = ft_calloc(len + 1, sizeof(*output));
	ft_memcpy(output, start, len);
	output = ft_first_traduction(output);
	ft_printf("ARGS_ASSEMBLER : %s\n", output);
	ft_env_test(output);
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
	while (line_read[++i])
	{
		if (line_read[i] == '\"' && single_quotes == 1)
			double_quotes *= -1;
		if (line_read[i] == '\'' && double_quotes == 1)
			single_quotes *= -1;
		if(single_quotes == -1 || double_quotes == -1)
			quotes_status = -1;
		else
			quotes_status = 1;	
		if (line_read[i] == '|' && !arg_start)
		{
			arg_start = &line_read[i];
			arg_end = &line_read[i];
		}
		if (!ft_is_space_tab(line_read[i]) && !arg_start)
			arg_start = &line_read[i];
		if (line_read[i + 1] == '|' && arg_start && quotes_status == 1 && !arg_end)
			arg_end = &line_read[i];
		if (ft_is_space_tab(line_read[i]) && arg_start && !arg_end && quotes_status == 1)
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
