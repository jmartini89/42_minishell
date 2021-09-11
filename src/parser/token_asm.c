#include "minishell.h"

static void	ft_token_translation_env(t_token *tkn)
{
	//
}

/* DUMMY CODE */
static void	ft_token_translation_quotes(t_token *tkn)
{
	char	*output;
	int		len;

	output = NULL;
	len = tkn->end - tkn->start + 1;
	output = ft_calloc(len + 1, sizeof(*output));
	ft_memcpy(output, tkn->start, len);
	ft_printf("ARGS_ASSEMBLER : %s\n", output);
	free (output);
	output = NULL;
}

void	ft_token_assembler(t_token *tkn)
{
	ft_token_init_quotes(tkn);
	ft_token_translation_quotes(tkn);
	ft_token_translation_env(tkn);
}
