#ifndef MINISHELL_UTILS_H
# define MINISHELL_UTILS_H

int	ft_is_metachar(char c);
int	ft_is_quote(char c);
int	ft_is_operator(char c);
int	ft_is_space_tab(char c);
int	ft_perror(int err);

#endif