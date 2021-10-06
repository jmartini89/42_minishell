#ifndef MSHELL_GC_H
# define MSHELL_GC_H

void	ft_gc(t_shell *shell);
void	ft_gc_arr_str(char **heap);
void	ft_gc_token(char **token, int *literal);

#endif