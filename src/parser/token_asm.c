#include "minishell.h"

static void	ft_token_translation_env(t_token *tkn)
{
	ft_printf("DOLLAR\n");
}

static void	ft_token_translation_quotes(t_token *tkn)
{
	char	*addr;
	char	*output;
	int		len;
	int		status;

	output = ft_calloc(tkn->end - tkn->start + 1, sizeof(*output));
	len = 0;
	addr = tkn->start;
	while (addr <= tkn->end)
	{
		status = tkn->s_qts * tkn->d_qts;
		ft_token_quotes(tkn, *addr);
		if (status == tkn->s_qts * tkn->d_qts)
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
