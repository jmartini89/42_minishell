/* MSHELL_PARSER */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mshell_parser.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jm & mc <jmartini & mcrisari>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 23:47:08 by jm & mc           #+#    #+#             */
/*   Updated: 2021/11/07 23:47:09 by jm & mc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSHELL_PARSER_H
# define MSHELL_PARSER_H
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
	int		literal_current;
	int		*lexer;
}	t_token;

int		ft_parser(char *line, t_shell *shell);
int		ft_token(char *line, t_token *tkn, t_shell *shell);
int		ft_lexer(t_token *tkn, t_shell *shell);

/* CMD */
void	ft_cmd(t_token *tkn, t_shell *shell);
void	ft_cmd_asm(t_token *tkn, t_shell *shell, t_list *word, t_redir *redir);
int		ft_cmd_cnt(t_token *tkn);
void	ft_word_cpy(t_shell *shell, t_list *word, int index);

/* SYNTAX CHECKS */
int		ft_line_syntax(char *line, t_shell *shell);
int		ft_lexer_syntax(t_token *tkn, t_shell *shell);

/* TOKEN_INIT */
void	ft_token_init_all(t_token *tkn);
void	ft_token_init_addr(t_token *tkn);
void	ft_token_init_quotes(t_token *tkn);

/* TOKEN_FIND*/
void	ft_token_find(t_token *tkn, char *c);
int		ft_token_quotes_status(t_token *tkn, char c);

/* TOKEN_TRANSLATE */
char	*ft_token_translate(t_token *tkn, t_shell *shell);

/* TOKEN_UTILS */
int		ft_is_metachar(char c);
int		ft_is_quote(char c);
int		ft_is_operator(char c);
int		ft_is_space_tab(char c);
int		ft_operator_type(char *arg);
int		ft_is_dollar_meta(char c);

#endif