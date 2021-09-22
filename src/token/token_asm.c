#include "minishell.h"

static char	*ft_token_expansion(t_token *tkn, t_shell *shell, char *addr)
{
	int		len;
	char	*tmp;
	char	*env;

	addr++;
	len = 0;
	while (&addr[len] <= tkn->end
		&& !ft_is_quote(addr[len]) && addr[len] != '$')
		len++;
	tmp = ft_calloc(len + 1, sizeof(*tmp));
	if (!tmp)
		ft_perror_exit(ERR_SYS_MALLOC);
	ft_memcpy(tmp, addr, len);
	env = ft_getenv(shell, tmp);
	free (tmp);
	return (env);
}

static int	ft_token_len(t_token *tkn, t_shell *shell)
{
	char	*addr;
	char	*env;
	int		len;

	addr = tkn->start;
	len = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes_status(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE)
			{
				env = ft_token_expansion(tkn, shell, addr);
				len += ft_strlen(env);
				while (*addr && !ft_is_quote(*addr) && *(addr + 1) != '$')
					addr++;
			}
			else
				len++;
		}
		addr++;
	}
	return (len);
}

static void	ft_token_write(t_token *tkn, t_tkn_tmp *tmp, t_shell *shell)
{
	if (!ft_token_quotes_status(tkn, *tmp->addr))
	{
		if (*tmp->addr == '$' && tkn->s_qts == QTS_CLOSE)
		{
			tmp->env = ft_token_expansion(tkn, shell, tmp->addr);
			while (tmp->env && *tmp->env)
			{
				tmp->token[tmp->i++] = *tmp->env;
				tmp->env++;
			}
			while (*tmp->addr
				&& !ft_is_quote(*tmp->addr) && *(tmp->addr + 1) != '$')
				tmp->addr++;
		}
		else
			tmp->token[tmp->i++] = *tmp->addr;
	}
}

static char	*ft_token_translate(t_token *tkn, t_shell *shell)
{
	t_tkn_tmp	tmp;

	tmp.token = ft_calloc(
			ft_token_len(tkn, shell) + 1, sizeof(*tmp.token));
	if (!tmp.token)
		ft_perror_exit(ERR_SYS_MALLOC);
	tmp.addr = tkn->start;
	tmp.i = 0;
	while (tmp.addr <= tkn->end)
	{
		ft_token_write(tkn, &tmp, shell);
		tmp.addr++;
	}
	return (tmp.token);
}

void	ft_token_assembler(t_token *tkn, t_shell *shell)
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
