#include "minishell.h"

int	g_signum = 0;

void	receive_signal(int sig)
{
	g_signum = sig;
	ft_putchar_fd('\n', STDIN_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	sig_heredoc(int sig)
{
	g_signum = sig;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_on_new_line();
}

void	handle_signals(bool heredoc)
{
	if (heredoc)
		signal(SIGINT, sig_heredoc);
	else
		signal(SIGINT, receive_signal);
	signal(SIGQUIT, SIG_IGN);
}
