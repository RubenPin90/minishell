#include "minishell.h"

int		g_signum = 0;

void	receive_signal(int sig)
{
	g_signum = sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	handle_signals(void)
{
	// if (status == HEREDOC)
	signal(SIGINT, receive_signal);
	signal(SIGQUIT, SIG_IGN);
}
