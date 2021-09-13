#ifndef MINISHELL_PARSER_H
# define MINISHELL_PARSER_H
# define PIPE 1
# define REDIR_R 2
# define REDIR_L 3
# define QTS_SINGLE 1
# define QTS_DOUBLE 2
# define QTS_OPEN -1
# define QTS_CLOSE 1

typedef struct s_token
{
	char	*start;
	char	*end;
	int		s_qts;
	int		d_qts;
	int		quotes_status;
}	t_token;

/* TOKEN */
int		ft_token(char *line);

/* PARSER */
int		ft_parser(char *line);

/* TOKEN_INIT */
void	ft_token_init_all(t_token *tkn);
void	ft_token_init_addr(t_token *tkn);
void	ft_token_init_quotes(t_token *tkn);

/* TOKEN_FIND*/
void	ft_token_find(t_token *tkn, char *c);
int		ft_token_quotes(t_token *tkn, char c);

/* TOKEN_ASM*/
void	ft_token_assembler(t_token *tkn);

/* TOKEN_UTILS */
int		ft_is_metachar(char c);
int		ft_is_quote(char c);
int		ft_is_operator(char c);
int		ft_is_space_tab(char c);

#endif