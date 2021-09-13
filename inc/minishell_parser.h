#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H
# define PIPE 1
# define REDIR_R 2
# define REDIR_L 3
# define QTS_SINGLE 1
# define QTS_DOUBLE 2
# define QTS_OPEN -1
# define QTS_CLOSE 1
# define QTS_ADDR_START 1
# define QTS_ADDR_END 2

typedef struct s_token
{
	char	*start;
	char	*end;
	int		s_qts;
	int		d_qts;
	int		quotes_status;
	int		len;
}	t_token;

int		ft_parser(char *line_read);
void	ft_token_init_all(t_token *tkn);
void	ft_token_init_addr(t_token *tkn);
void	ft_token_init_quotes(t_token *tkn);
int		ft_token_quotes(t_token *tkn, char c);
int		ft_validity_check(char *line_read);
void	ft_token(char *line);
void	ft_token_assembler(t_token *tkn);

#endif