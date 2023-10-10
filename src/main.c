/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:28:42 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 16:18:05 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (error_msg(NULL, NULL, ARGC_ERR, FAIL));
	init_data(&data);
	data.env = copy_envp(&data, envp);
	if (!data.env)
		return (ft_error(MALLOC_ERR, &data));
	while (1)
	{
		handle_signals(false, false);
		if (handle_input(&data) == SUCCESS)
			executor(&data);
		ft_cleanup(&data, false);
	}
	return (SUCCESS);
}
