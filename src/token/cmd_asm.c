#include "minishell.h"

static int
	ft_cmd_counter(t_token *tkn)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 1;
	while (tkn->token[i])
	{
		if (ft_is_operator(tkn->token[i][0]) && !tkn->tkn_literal[i])
		{
			if (i)
				cnt++;
			if (tkn->token[i + 1])
			{
				if ((ft_is_operator(tkn->token[i + 1][0])
					&& tkn->tkn_literal[i + 1])
					|| !ft_is_operator(tkn->token[i + 1][0]))
					cnt++;
			}
		}
		i++;
	}
	return (cnt);
}

static int
	ft_cmd_sub_counter(t_token *tkn, int i)
{
	int	cnt;

	cnt = 0;
	while (tkn->token[i])
	{
		cnt++;
		if (ft_is_operator(tkn->token[i][0])
			&& !tkn->tkn_literal[i])
			return (cnt);
		if (tkn->token[i + 1]
			&& ft_is_operator(tkn->token[i + 1][0])
			&& !tkn->tkn_literal[i + 1])
			return (cnt);
		i++;
	}
	return (cnt);
}

static void
	ft_cmd_write(t_token *tkn, t_shell *shell, int cmd_cnt)
{
	int	i;
	int	j;
	int	k;
	int	sub_cnt;

	i = 0;
	j = 0;
	while (i < cmd_cnt)
	{
		sub_cnt = ft_cmd_sub_counter(tkn, j);
		shell->cmd[i] = ft_calloc(sub_cnt + 1, sizeof(**shell->cmd));
		if (!shell->cmd[i])
			ft_perrno_exit(ERR_SYS_MALLOC, 1);
		if (ft_is_operator(tkn->token[j][0]) && !tkn->tkn_literal[j])
			shell->cmd_operator[i] = 1;
		k = 0;
		while (k < sub_cnt)
		{
			shell->cmd[i][k] = tkn->token[j];
			j++;
			k++;
		}
		i++;
	}
}

void
	ft_cmd_asm(t_token *tkn, t_shell *shell)
{
	int	i;
	int	j;
	int	k;
	int	cmd_cnt;
	int	sub_cnt;

	cmd_cnt = ft_cmd_counter(tkn);
	shell->cmd = ft_calloc(cmd_cnt + 1, sizeof(*shell->cmd));
	shell->cmd_operator = ft_calloc(cmd_cnt, sizeof(*shell->cmd_operator));
	if (!shell->cmd || !shell->cmd_operator)
		ft_perrno_exit(ERR_SYS_MALLOC, 1);
	ft_cmd_write(tkn, shell, cmd_cnt);
	free (tkn->token);
	free (tkn->tkn_literal);
}
