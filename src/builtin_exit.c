/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:26 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 16:44:25 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	check_exit(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return (SUCCESS);
	if (arg[i] == '\0')
		return (FAIL);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (FAIL);
		i++;
	}
	return (SUCCESS);
}

int	ft_exit(t_data *data, t_parse *cmd)
{
	int	num_args;

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd)
	{
		num_args = ft_arrlen(cmd->cmd);
		if (num_args > 1 && check_exit(cmd->cmd[1]))
			data->excode = error_msg("exit", cmd->cmd[1], NUM_ERR, E_SYNERR);
		else if (num_args > 2)
			return (error_msg("exit", NULL, ARG_ERR, E_ERROR));
		else if (num_args == 2)
			data->excode = ft_atoi(cmd->cmd[1]);
		else
			data->excode = 0;
	}
	switch_stdfd(data, cmd, data->stdfd, false);
	ft_cleanup(data, true);
	return (SUCCESS);
}
