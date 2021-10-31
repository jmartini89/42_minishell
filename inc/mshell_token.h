#ifndef MSHELL_TOKEN_H
# define MSHELL_TOKEN_H
# define WORD 00
# define PIPE 01
# define R_OUT 02
# define APPEND 04
# define R_IN 010
# define HERE 020
# define QTS_SINGLE 1
# define QTS_DOUBLE 2
# define QTS_OPEN -1
# define QTS_CLOSE 1

typedef struct s_tkn_tmp
{
	char	*addr;
	char	*token;
	char	*env;
	int		i;
}	t_tkn_tmp;

typedef struct s_token
{
	char	*start;
	char	*end;
	int		s_qts;
	int		d_qts;
	int		quotes_status;
	char	**token;
	int		*tkn_literal;
	int		literal;
}	t_token;

/* TOKEN */
int		ft_token(char *line, t_shell *shell);
void	ft_cmd_asm(t_token *tkn, t_shell *shell);

/* SYNTAX */
int		ft_line_syntax(char *line, t_shell *shell);

/* TOKEN_INIT */
void	ft_token_init_all(t_token *tkn);
void	ft_token_init_addr(t_token *tkn);
void	ft_token_init_quotes(t_token *tkn);

/* TOKEN_FIND*/
void	ft_token_find(t_token *tkn, char *c);
int		ft_token_quotes_status(t_token *tkn, char c);

/* TOKEN_EXP*/
char	*ft_token_translate(t_token *tkn, t_shell *shell);

/* TOKEN_UTILS */
int		ft_is_metachar(char c);
int		ft_is_quote(char c);
int		ft_is_operator(char c);
int		ft_is_space_tab(char c);
int		ft_operator_type(char *arg);

#endif