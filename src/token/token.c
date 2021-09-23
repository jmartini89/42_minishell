#include "minishell.h"

static int	ft_token_assembler_swap(t_shell *shell)
{
	int		len;
	int		i;
	char	**tmp;

	tmp = shell->token;
	len = 0;
	while (tmp && tmp[len])
	{
		tmp[len] = shell->token[len];
		len++;
	}
	shell->token = ft_calloc(len + 2, sizeof(*shell->token));
	if (!shell->token)
		ft_perror_exit(ERR_SYS_MALLOC);
	i = 0;
	while (tmp && tmp[i])
	{
		shell->token[i] = tmp[i];
		i++;
	}
	free (tmp);
	return (len);
}

static void	ft_token_assembler(t_token *tkn, t_shell *shell)
{
	int		len;
	char	*new_tkn;

	ft_token_init_quotes(tkn);
	new_tkn = ft_token_translate(tkn, shell);
	if (*new_tkn)
	{
		len = ft_token_assembler_swap(shell);
		shell->token[len] = new_tkn;
		ft_printf("TOKEN : %s\n", shell->token[len]);
	}
	else
		free (new_tkn);
}

int	ft_token(char *line, t_shell *shell)
{
	t_token	tkn;
	int		i;

	if (!ft_syntax(line))
		return (0);
	shell->token = NULL;
	ft_token_init_all(&tkn);
	i = -1;
	while (line[++i])
	{
		ft_token_find(&tkn, &line[i]);
		if (tkn.end)
		{
			ft_token_assembler(&tkn, shell);
			ft_token_init_all(&tkn);
		}
	}
	if (shell->token)
		return (1);
	return (0);
}
