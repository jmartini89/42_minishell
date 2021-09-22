#include "minishell.h"

static void	ft_token_assembler(t_token *tkn, t_shell *shell)
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
	ft_token_init_quotes(tkn);
	shell->token[len] = ft_token_translate(tkn, shell);
	free (tmp);
	ft_printf("TOKEN : %s\n", shell->token[len]);
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
	return (1);
}
