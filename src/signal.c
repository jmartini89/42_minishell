#include "minishell.h"

static void	ft_sig_int(int sig)
{
	ft_printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_sig_void(int sig)
{
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_void);
}
