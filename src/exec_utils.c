/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:15:04 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 14:15:05 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	create_pipes(t_parse *cmd_line, int cmds)
{
	int	i;

	i = 0;
	while (cmd_line->id != 0)
	{
		if (++i < cmds)
		{
			if (pipe(cmd_line->fd_pipes) == -1)
				return (error_msg("pipe", NULL, strerror(errno), AGAIN));
		}
		cmd_line++;
	}
	return (SUCCESS);
}

int	ft_dup2(int fdin, int fdout)
{
	if (fdin > 0)
		if (dup2(fdin, STDIN_FILENO) < 0)
			return (error_msg("Infile", NULL, strerror(errno), FAIL));
	if (fdout > 0)
		if (dup2(fdout, STDOUT_FILENO) < 0)
			return (error_msg("Outfile", NULL, strerror(errno), FAIL));
	return (SUCCESS);
}

void	fdmulti_redef(t_parse *cmd, int *tmp_fdout, int *tmp_fdin, int cmds)
{
	t_parse	*prev_cmd;

	if (cmd->id > 1)
		prev_cmd = cmd - 1;
	*tmp_fdin = STDIN_FILENO;
	*tmp_fdout = STDOUT_FILENO;
	if (cmd->id == 1)
		*tmp_fdout = cmd->fd_pipes[1];
	else if (cmd->id > 1 && cmd->id < cmds)
	{
		*tmp_fdin = prev_cmd->fd_pipes[0];
		*tmp_fdout = cmd->fd_pipes[1];
	}
	else
		*tmp_fdin = prev_cmd->fd_pipes[0];
}

void	replace_fdmulti(t_data *data, t_parse *cmd)
{
	int		tmp_fdout;
	int		tmp_fdin;

	fdmulti_redef(cmd, &tmp_fdout, &tmp_fdin, data->cmds);
	if (cmd->id >= 1)
	{
		if (cmd->fd_out > 0)
			ft_dup2(tmp_fdin, cmd->fd_out);
		else if (cmd->fd_in > 0)
			ft_dup2(cmd->fd_in, tmp_fdout);
		else
			ft_dup2(tmp_fdin, tmp_fdout);
	}
}

void	replace_fd(t_data *data, t_parse *cmd)
{
	if (cmd->fd_in > 0 && cmd->fd_out > 0)
		ft_dup2(cmd->fd_in, cmd->fd_out);
	else if (data->cmds == 1)
	{
		if (cmd->fd_in > 0)
			ft_dup2(cmd->fd_in, 1);
		else if (cmd->fd_out > 0)
			ft_dup2(0, cmd->fd_out);
	}
	else
		replace_fdmulti(data, cmd);
	close_all_fds(data->cmd_line);
}
