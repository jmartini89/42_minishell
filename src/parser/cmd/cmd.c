#include "minishell.h"

static int
	ft_cmd_cnt(t_token *tkn)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (tkn->token[i])
	{
		if (tkn->lexer[i] == PIPE)
			cnt++;
		i++;
	}
	return (cnt + 1);
}

static void
	ft_lstcpy(t_shell *shell, t_list *word, int index)
{
	int		i;

	i = 0;
	while (word)
	{
		shell->cmd[index].argv[i] = word->content;
		word = word->next;
		i++;
	}
}

static void
	ft_cmd_word(t_token *tkn, t_list **word, int i)
{
	t_list	*tmp;

	tmp = NULL;
	tmp = ft_lstnew(tkn->token[i]);
	if (tmp == NULL)
		ft_error_exit(errno, "malloc", EXIT_FAILURE);
	if (word == NULL)
		*word = tmp;
	else
		ft_lstadd_back(word, tmp);
}

static void
	ft_cmd_redir(t_token *tkn, t_redir **redir, int i)
{
	t_redir	*tmp;

	tmp = NULL;
	tmp = ft_rdr_new(tkn->lexer[i], tkn->token[i + 1]);
	if (redir == NULL)
		*redir = tmp;
	else
		ft_rdr_add_back(redir, tmp);
	free (tkn->token[i]);
	tkn->token[i] = NULL;
}

static void
	ft_cmd_asm(t_token *tkn, t_shell *shell)
{
	t_list	*word;
	t_redir	*redir;
	int		lstsize;
	int		i;
	int		cnt;

	word = NULL;
	redir = NULL;

	shell->cmd_cnt = ft_cmd_cnt(tkn);
	shell->cmd = ft_calloc(shell->cmd_cnt, sizeof(*shell->cmd));

	cnt = 0;
	i = 0;
	int test = 0;
	while (tkn->token[i])
	{
		if (tkn->token[i] && tkn->lexer[i] == WORD)
		{
			ft_cmd_word(tkn, &word, i);
			i++;
		}

		if (tkn->token[i] && tkn->lexer[i] > PIPE)
		{
			ft_cmd_redir(tkn, &redir, i);
			i += 2;
		}

		if ((tkn->token[i] && tkn->lexer[i] == PIPE)
			|| tkn->token[i] == NULL)
		{

			ft_printf("---CMD %d---\n", cnt);
			if (tkn->token[i] && tkn->lexer[i] == PIPE)
			{
				free (tkn->token[i]);
				tkn->token[i] = NULL;
				i++;
			}

			shell->cmd[cnt].argv = NULL;
			shell->cmd[cnt].redir = redir;

			lstsize = ft_lstsize(word);
			if (lstsize)
			{
				shell->cmd[cnt].argv = ft_calloc(lstsize + 1, sizeof(*shell->cmd[cnt].argv));
				if (shell->cmd[cnt].argv == NULL)
					ft_error_exit(errno, "malloc", EXIT_FAILURE);
			}
			ft_lstcpy(shell, word, cnt);

			redir = NULL;
			ft_lstclear(&word, NULL);

			/* PRINT TEST */
			while (shell->cmd[cnt].argv && shell->cmd[cnt].argv[test])
			{
				ft_printf("WORD\t%s\n", shell->cmd[cnt].argv[test]);
				test++;
			}
			ft_rdr_iter(shell->cmd[cnt].redir, ft_rdr_print);
			test = 0;
			ft_printf("-----------\n", cnt);

			cnt++;
		}
	}

	// ft_gc_cmd(shell);
}

void
	ft_cmd(t_token *tkn, t_shell *shell)
{
	shell->cmd = NULL;
	shell->cmd_cnt = 0;
	ft_cmd_asm(tkn, shell);
}
