#ifndef MSHELL_LIBLIST_H
# define MSHELL_LIBLIST_H

t_redir	*ft_rdr_new(int type, char *name);
void	ft_rdr_clear(t_redir **lst, void (*del)(void *));
t_redir	*ft_rdr_last(t_redir *lst);
void	ft_rdr_add_back(t_redir **lst, t_redir *new);
void	ft_rdr_iter(t_redir *lst, void (*f)(int type, char *name));

/*UTILS*/
void	ft_lstprint(void *content);
void	ft_rdr_print(int type, char *name);

#endif