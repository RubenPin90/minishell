/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:14:55 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 14:25:53 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	exec_child(t_data *data, t_parse *cmd, char *cmdpath)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (error_msg("fork", NULL, strerror(errno), E_ERROR));
	if (cmd->pid > 1)
		signal(SIGINT, SIG_IGN);
	if (cmd->pid == 0)
	{
		handle_signals(false);
		replace_fd(data, cmd);
		if (cmd->execute == false)
		{
			data->excode = print_warning(cmd, cmd->exstatus);
			ft_cleanup(data, true);
		}
		if (execve(cmdpath, cmd->cmd, data->env_arr) == -1)
		{
			data->excode = error_msg(cmd->cmd[0], "child", \
											strerror(errno), E_ERROR);
			ft_cleanup(data, true);
		}
	}
	return (SUCCESS);
}

int	exec_builtin(t_data *data, t_parse *cmd, bool parent)
{
	if (parent == true)
	{
		switch_stdfd(data, cmd, data->stdfd, true);
		data->excode = cmd->func(data, cmd);
		switch_stdfd(data, cmd, data->stdfd, false);
	}
	else
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (error_msg("fork", NULL, strerror(errno), E_ERROR));
		if (cmd->pid == 0)
		{
			replace_fd(data, cmd);
			data->excode = cmd->func(data, cmd);
			ft_cleanup(data, true);
		}
	}
	return (SUCCESS);
}

int	exec_single_cmd(t_parse *cmd, bool parent, t_data *data)
{
	if (cmd->execute == false)
	{
		data->excode = print_warning(cmd, cmd->exstatus);
		return (SUCCESS);
	}
	if (cmd->func)
		exec_builtin(data, cmd, parent);
	else
		exec_child(data, cmd, cmd->cmd_path);
	cleanup_fd(&cmd->fd_in);
	cleanup_fd(&cmd->fd_out);
	ft_waitpid(data, cmd);
	return (SUCCESS);
}

int	exec_multi_cmds(t_parse *cmd_line, int cmds, t_data *data)
{
	create_pipes(data->cmd_line, cmds);
	while (cmd_line->id != 0)
	{
		if (cmd_line->func)
			exec_builtin(data, cmd_line, false);
		else
			exec_child(data, cmd_line, cmd_line->cmd_path);
		cmd_line++;
	}
	close_all_fds(data->cmd_line);
	ft_waitpid(data, data->cmd_line);
	return (SUCCESS);
}

int	executor(t_data *data)
{
	g_signum = 0;
	data->env_arr = list_to_arr(data, data->env);
	handle_heredoc(data, data->cmd_line);
	handle_fds(data->cmd_line);
	cmdfinder(data, data->cmd_line);
	if (data->cmds == 1)
		exec_single_cmd(data->cmd_line, data->cmd_line->parent, data);
	else
		exec_multi_cmds(data->cmd_line, data->cmds, data);
	return (SUCCESS);
}
