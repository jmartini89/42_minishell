#include "minishell.h"

static char	*ft_token_pre_env(t_token *tkn, char *addr)
{
	int		len;
	char	*tmp;

	addr++;
	tmp = NULL;
	len = 0;
	while (&addr[len] <= tkn->end && !ft_is_quote(addr[len]))
		len++;
	tmp = ft_calloc(len + 1, sizeof(*tmp));
	if (!tmp)
		return (0);
	ft_memcpy(tmp, addr, len);
	return (tmp);
}

static char	*ft_token_env(t_token *tkn, char *pre_env)
{
	char	*env;

	env = getenv(pre_env);
	free (pre_env);
	return (env);
}

static int	ft_token_len(t_token *tkn)
{
	char	*addr;
	char	*pre_env;
	char	*env;
	int		len;

	addr = tkn->start;
	len = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE)
			{
				pre_env = ft_token_pre_env(tkn, addr);
				if (!pre_env)
					return (0);
				env = ft_token_env(tkn, pre_env);
				len += ft_strlen(env);
				while (*addr && !ft_is_quote(*addr))
					addr++;
			}
			else
				len++;
		}
		addr++;
	}
	return (len);
}

static char	*ft_token_translate(t_token *tkn)
{
	char	*addr;
	char	*token;
	char	*pre_env;
	char	*env;
	int		i;

	token = NULL;
	token = ft_calloc(ft_token_len(tkn) + 1, sizeof(*token));
	if (!token)
		return (0);
	addr = tkn->start;
	i = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE)
			{
				pre_env = ft_token_pre_env(tkn, addr);
				if (!pre_env)
					return (0);
				env = ft_token_env(tkn, pre_env);
				while (env && *env)
				{
					token[i++] = *env;
					env++;
				}
				while (*addr && !ft_is_quote(*addr))
					addr++;
			}
			else
				token[i++] = *addr;
		}
		addr++;
	}
	return (token);
}

int	ft_token_assembler(t_token *tkn)
{
	char	*tmp;

	tmp = NULL;
	ft_token_init_quotes(tkn);
	tmp = ft_token_translate(tkn);
	if (!tmp)
		return (0);
	ft_printf("%s\n", tmp);
	free (tmp);
	return (1);
}
