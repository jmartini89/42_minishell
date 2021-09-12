#include "minishell.h"

static void	ft_token_translation_env(t_token *tkn)
{
	ft_printf("ENV\n");
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
			len++;
		addr++;
	}
	return (len);
}

static void	ft_token_translation_quotes(t_token *tkn)
{
	char	*addr;
	char	*output;
	int		len;

	len = ft_token_translation_quotes_len(tkn);
	output = ft_calloc(len + 1, sizeof(*output));
	addr = tkn->start;
	len = 0;
	while (addr <= tkn->end)
	{
		if (!ft_token_quotes(tkn, *addr))
		{
			if (*addr == '$' && tkn->s_qts == QTS_CLOSE)
				ft_token_translation_env(tkn);
			output[len] = *addr;
			len++;
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
