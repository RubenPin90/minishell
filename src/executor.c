
#include "executor.h"

int	exec_child(t_data *data, t_parse *cmd, char *cmdpath)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (error_msg("fork", NULL, strerror(errno)));
	if (cmd->pid == 0)
	{
		replace_fd(data, cmd);
		execve(cmdpath, cmd->cmd, data->env_arr);
	}
	return (SUCCESS);
}

int	exec_builtin(t_data *data, t_parse *cmd, bool parent)
{
	if (parent == true)
	{
		if(cmd->func(data, cmd))
			return (FAIL);
	}
	else
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			return (error_msg("fork", NULL, strerror(errno)));
		if (cmd->pid == 0)
		{
			replace_fd(data, cmd);
			cmd->func(data, cmd);
			exit(0);
		}
	}
	return(SUCCESS);
}

int	exec_single_cmd(t_parse *cmd, bool parent, t_data *data)
{
	int		status;

	if (cmd->execute == false)
		return (SUCCESS);
	if (cmd->func)
		exec_builtin(data, cmd, parent);
	else
		exec_child(data, cmd, cmd->cmd_path);
	cleanup_fd(&cmd->fd_in);
	cleanup_fd(&cmd->fd_out);
	waitpid(cmd->pid, &status, 0);
	return (SUCCESS);
}

int	exec_multi_cmds(t_parse *cmd_line, int cmds, t_data *data)
{
	t_parse *tmp;
	int status;

	tmp = cmd_line;
	create_pipes(data->cmd_line, cmds);
	while (cmd_line->id != 0)
	{
		if (cmd_line->execute && cmd_line->func)
			exec_builtin(data, cmd_line, false);
		else if (cmd_line->execute)
			exec_child(data, cmd_line, cmd_line->cmd_path);
		cmd_line++;
	}
	close_all_fds(data->cmd_line);
	while (tmp->id != 0)
	{
		waitpid(tmp->pid, &status, 0);
		tmp++;
	}
	return (SUCCESS);
}

int executor(t_data *data)
{
	data->env_arr = list_to_arr(data, data->env);
	handle_heredoc(data, data->cmd_line);
	if (cmdfinder(data, data->cmd_line))
		return(AGAIN);
	if (handle_fds(data, data->cmd_line))
		return(AGAIN);
	if (data->cmds == 1)
		exec_single_cmd(data->cmd_line, data->cmd_line->parent, data);
	else
		exec_multi_cmds(data->cmd_line, data->cmds, data);
	return (SUCCESS);	
}
