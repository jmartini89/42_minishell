#include "minishell.h"

static char	*ft_token_expansion_alloc(t_token *tkn, char *addr)
{
	int		len;
	char	*tmp;

	addr++;
	tmp = NULL;
	len = 0;
	while (&addr[len] <= tkn->end && !ft_is_quote(addr[len]) && addr[len] != '$')
		len++;
	tmp = ft_calloc(len + 1, sizeof(*tmp));
	if (!tmp)
		return (0);
	ft_memcpy(tmp, addr, len);
	return (tmp);
}

static char	*ft_token_expansion(t_token *tkn, t_shell *shell, char *addr)
{
	char	*env;

	env = ft_getenv(shell, addr);
	free (addr);
	return (env);
}

static int	ft_token_len(t_token *tkn, t_shell *shell)
{
	char	*addr;
	char	*pre_env;
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
				pre_env = ft_token_expansion_alloc(tkn, addr);
				if (!pre_env)
					return (0);
				env = ft_token_expansion(tkn, shell, pre_env);
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

static char	*ft_token_translate(t_token *tkn, t_shell *shell)
{
	char	*addr;
	char	*token;
	char	*pre_env;
	char	*env;
	int		i;

	token = NULL;
	token = ft_calloc(ft_token_len(tkn, shell) + 1, sizeof(*token));// !!! UNPROTECTED token_len !!!
	if (!token)
		return (0);
	addr = tkn->start;
	i = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes_status(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE) // PARAMETER EXPANSION
			{
				pre_env = ft_token_expansion_alloc(tkn, addr);
				if (!pre_env)
					return (0);
				env = ft_token_expansion(tkn, shell, pre_env);
				while (env && *env)
				{
					token[i++] = *env;
					env++;
				}
				while (*addr && !ft_is_quote(*addr) && *(addr + 1) != '$')
					addr++;
			}
			else
				token[i++] = *addr;
		}
		addr++;
	}
	return (token);
}

int	ft_token_assembler(t_token *tkn, t_shell *shell)
{
	int		len;
	char	**tmp;

	tmp = tkn->token;
	len = -1;
	while (tmp && tmp[++len])
		tmp[len] = tkn->token[len];
	tkn->token = ft_calloc(len + 2, sizeof(*tkn->token));
	if (!tkn->token)
		return (0);
	ft_token_init_quotes(tkn);
	len = -1;
	while (tmp && tmp[++len])
		tkn->token[len] = tmp[len];
	len += 1;
	tkn->token[len] = ft_token_translate(tkn, shell);
	if (!tkn->token[len])
		return (0);
	ft_printf("%s\n", tkn->token[len]);
	free (tmp);
	return (1);
}
