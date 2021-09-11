#include "minishell.h"

static void	ft_token_translation_env(t_token *tkn)
{
	//
}

static void	ft_token_translation_quotes(t_token *tkn)
{
	int	len;

	if (tkn->quotes)
	{
		len = -1;
		while (tkn->quotes[++len])
			ft_printf("QTS DEBUG ASM\t: %d\t%p\n", len, tkn->quotes[len]);
	}
	free (tkn->quotes);
}

void	ft_token_assembler(t_token *tkn)
{
	char	*output;
	int		len;

	output = NULL;
	ft_token_translation_quotes(tkn);
	len = tkn->end - tkn->start + 1;
	output = ft_calloc(len + 1, sizeof(*output));
	ft_memcpy(output, tkn->start, len);
	ft_printf("ARGS_ASSEMBLER : %s\n", output);
	free (output);
	output = NULL;
}
