/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rubsky <rubsky@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:25:06 by rubsky            #+#    #+#             */
/*   Updated: 2023/07/03 17:46:41 by rubsky           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	main(int argc, char **argv, char **envp)
{
	struct sigaction	sigact;

	(void)argv;
	(void)envp;
	if (argc != 1)
		return (1);
	sigact.sa_sigaction = receive_signal;
	sigemptyset(&sigact.sa_mask);
    sigaddset(&sigact.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sigact, NULL);
	sigaction(SIGQUIT, &sigact, NULL);
	while (1)
	{

	}
	return (0);
}

