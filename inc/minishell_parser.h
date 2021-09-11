#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H
# define PIPE 1
# define REDIR_R 2
# define REDIR_L 3

typedef struct s_token
{
	char	*start;
	char	*end;
	int		s_qts;
	int		d_qts;
	int		quotes_status;
	char	*s_qts_start;
	char	*s_qts_end;
	char	*d_qts_start;
	char	*d_qts_end;
}	t_token;

int		ft_parser(char *line_read);
int		ft_validity_check(char *line_read);
void	ft_token(char *line);
void	ft_token_assembler(t_token *tkn);

#endif