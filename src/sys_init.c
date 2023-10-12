/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:29:18 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/12 14:05:52 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_data(t_data *data)
{
	data->cmds = 0;
	data->paths = NULL;
	data->cmd_line = NULL;
	data->lex = NULL;
	data->env = NULL;
	data->env_arr = NULL;
	data->input = NULL;
	data->exp_lst = NULL;
	data->quoted = false;
	data->expand = true;
	data->word = NULL;
	data->stdfd[0] = -1;
	data->stdfd[1] = -1;
	data->excode = 0;
	data->exp_equal = false;
}

void	init_parse(t_parse *cmd_line, int len)
{
	int	i;

	i = 1;
	while (i < len)
	{
		cmd_line->id = i;
		cmd_line->fd_in = -1;
		cmd_line->fd_out = -1;
		cmd_line->fd_pipes[0] = -1;
		cmd_line->fd_pipes[1] = -1;
		cmd_line->execute = true;
		cmd_line->exstatus = E_SUCCESS;
		cmd_line->pid = 0;
		cmd_line++;
		i++;
	}
	cmd_line->id = 0;
}
