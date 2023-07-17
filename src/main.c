/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 12:25:06 by rpinchas          #+#    #+#             */
/*   Updated: 2023/07/14 14:37:55 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data				data;

	(void)argv;
	if (argc != 1)
		return (1);
	data.envp = copy_envp(envp);
	handle_signals();
	while (1)
	{
		if (handle_input(&data))
			break ;
			//save_data_history();
		//parser();
		//expander();
		//executer();
		//free;
	}
	return (0);
}

