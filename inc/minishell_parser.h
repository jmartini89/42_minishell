#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H
# define PIPE 1
# define REDIR_R 2
# define REDIR_L 3

typedef struct s_token
{
	char	*start;
	char	*end;
	int		single_quotes;
	int		double_quotes;
	int		quotes_status;
}	t_token;

int		ft_parser(char *line_read);
int		ft_validity_check(char *line_read);
void	ft_token(char *line);

#endif