/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapostol <aapostol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:27:44 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/14 16:04:44 by aapostol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
