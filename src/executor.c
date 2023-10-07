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
		execve(cmdpath, cmd->cmd, data->env_arr);
	}
	return (SUCCESS);
}

int	exec_builtin(t_data *data, t_parse *cmd, bool parent)
{
	if (parent == true)
		data->excode = cmd->func(data, cmd);
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
		data->excode = cmd->exstatus;
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
		if (cmd_line->execute && cmd_line->func)
			exec_builtin(data, cmd_line, false);
		else if (cmd_line->execute)
			exec_child(data, cmd_line, cmd_line->cmd_path);
		else
			data->excode = cmd_line->exstatus;
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
	cmd_printer(data);
	if (handle_heredoc(data, data->cmd_line))
		return (AGAIN);
	if (handle_fds(data->cmd_line))
		return (AGAIN);
	if (cmdfinder(data, data->cmd_line))
		return (AGAIN);
	if (data->cmds == 1)
		exec_single_cmd(data->cmd_line, data->cmd_line->parent, data);
	else
		exec_multi_cmds(data->cmd_line, data->cmds, data);
	return (SUCCESS);
}
