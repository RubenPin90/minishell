/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:29:04 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 16:57:03 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"

int	error_msg(char *cmd, char *arg, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		if (arg)
		{
			ft_putstr_fd("`", 2);
			ft_putstr_fd(arg, 2);
			ft_putstr_fd("'", 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(msg, 2);
	}
	else
		ft_putendl_fd(msg, 2);
	return (ret);
}

int	ft_error(char *msg, t_data *data)
{
	ft_putendl_fd(msg, 2);
	data->excode = E_ERROR;
	if (data)
		ft_cleanup(data, true);
	return (1);
}

void	ft_parent_error(char *msg, t_data *data, t_parse *cmd)
{
	if (cmd->pid == 0)
		switch_stdfd(data, cmd, data->stdfd, false);
	ft_error(msg, data);
}

t_status	print_warning(t_parse *cmdl, t_status err)
{
	if (err == E_NOENT)
		return (error_msg(cmdl->cmd[0], NULL, FD_NONEX_ERR, 127));
	else if (err == E_NOPERMS)
		return (error_msg(cmdl->cmd[0], NULL, FD_ACCESS_ERR, 126));
	else if (err == E_ISDIR)
		return (error_msg(cmdl->cmd[0], NULL, ISDIR_ERR, E_ISDIR));
	else if (err == E_NOCMD)
		return (error_msg(cmdl->cmd[0], NULL, NOTFOUND_ERR, E_NOCMD));
	return (err);
}
