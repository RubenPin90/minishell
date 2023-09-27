#include "minishell.h"

void	ignore_signal(int sig)
{
	(void)sig;
	return ;
}

// SIGINT needs to interupt programs with \n.
void	receive_signal(int sig)
{
	(void)sig;
	printf("You pressed CTRL + C\n");
	exit (0);
}

void	handle_signals(void)
{
	signal(SIGINT, receive_signal);
	signal(SIGABRT, ignore_signal);
}
