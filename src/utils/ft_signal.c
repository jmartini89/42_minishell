#include "minishell.h"

static void	ft_sig_int(int sig)
{
	ft_printf("^C\n");//BUG IF FORKED
	rl_on_new_line();
	rl_replace_line("", 0);
	ft_printf("DEBUG %d\n", g_pid);
	if (getpid() == g_pid) /* WHAT IS THIS FOR? */
		rl_redisplay();
}

static void	ft_sig_quit(int sig)
{
}

void	ft_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ft_sig_int);
	signal(SIGQUIT, ft_sig_quit);
}
