#include "minishell.h"

void
	ft_sig_int(int sig)
{
	(void)sig;
	ft_printf("^C\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void
	ft_signal_default(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void
	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, SIG_IGN);
}
