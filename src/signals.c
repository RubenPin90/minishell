
#include "minishell.h"

void	handle_signals()
{
	struct sigaction	sigact;

	sigact.sa_sigaction = receive_signal;
	sigemptyset(&sigact.sa_mask);
	sigaddset(&sigact.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
}

/*SIGINT needs to interupt programs with \n.
*/
void	receive_signal(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGINT)
	{
		printf("\n");
		exit (0);
	}
}
