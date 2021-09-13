#include "minishell.h"

static char	*ft_env_test(t_token *tkn, char *addr)
{
	int		len;
	char	*tmp;
	char	*env_test;

	len = 0;
	tmp = NULL;
	addr++;
	while (addr[len] && &addr[len] <= tkn->end && !ft_is_quote(addr[len]))
		len++;
	tmp = ft_calloc(len + 1, sizeof(*tmp));
	ft_memcpy(tmp, addr, len);
	env_test = getenv(tmp);
	free (tmp);
	return (env_test);
}

static int	ft_token_translation_quotes_len(t_token *tkn)
{
	char	*addr;
	int		len;

	addr = tkn->start;
	len = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE)
			{
				len += ft_strlen(ft_env_test(tkn, addr));
				while (*addr && !ft_is_quote(*addr))
					addr++;
			}
			else
				len++;
		}
		addr++;
	}
	//ft_printf("%d\n", len);
	return (len);
}

static void	ft_token_translation_quotes(t_token *tkn)
{
	char	*addr;
	char	*tmp;
	char	*output;
	int		i;

	output = ft_calloc(
			ft_token_translation_quotes_len(tkn) + 1, sizeof(*output));
	addr = tkn->start;
	i = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE)
			{
				tmp = ft_env_test(tkn, addr);
				while (tmp && *tmp)
				{
					output[i] = *tmp;
					i++;
					tmp++;
				}
				while (*addr && !ft_is_quote(*addr))
					addr++;
			}
			else
			{
				output[i] = *addr;
				i++;
			}
		}
		addr++;
	}
	ft_printf("ARGS_ASSEMBLER : %s\n", output);
	free (output);
	output = NULL;
}

void	ft_token_assembler(t_token *tkn)
{
	ft_token_init_quotes(tkn);
	ft_token_translation_quotes(tkn);
}
