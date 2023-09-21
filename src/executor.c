
#include "executor.h"

int	create_pipes(t_parse *cmd_line, int cmds)
{
	int i;

	i = 0;
	while(cmd_line->id != 0)
	{
		if (++i < cmds)
		{
			if (pipe(cmd_line->fd_pipes) == -1)
				return (error_msg("pipe", strerror(errno)));
		}
		cmd_line++;
	}
	return (SUCCESS);
}

int	ft_dup2(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		return (error_msg("Infile", strerror(errno)));
	if (dup2(fdout, STDOUT_FILENO) < 0)
		return (error_msg("Outfile", strerror(errno)));
	return (SUCCESS);
}

void	replace_fdmulti(t_data *data, t_parse *cmd)
{
	t_parse *prev_cmd;
	int		tmp_fdout;
	int		tmp_fdin;
	
	if (cmd->id > 1)
		prev_cmd = cmd - 1;
	tmp_fdin = STDIN_FILENO;
	tmp_fdout = STDOUT_FILENO;
	if (cmd->id == 1)
		tmp_fdout = cmd->fd_pipes[1];
	else if (cmd->id > 1 && cmd->id < data->cmds)
	{
		tmp_fdin = prev_cmd->fd_pipes[0];
		tmp_fdout = cmd->fd_pipes[1];
	}
	else
		tmp_fdin = prev_cmd->fd_pipes[0];
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

int	exec_child(t_data *data, t_parse *cmd, char *cmdpath)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		return (error_msg("fork", strerror(errno)));
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
		if (cmd->pid == 0)
		{
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
	// cmd_printer(data);
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
	int	err;

	err = 0;
	data->env_arr = list_to_arr(data, data->env);
	// cmd_printer(data);
	handle_heredoc(data, data->cmd_line);
	if (cmdfinder(data, data->cmd_line))
		return(AGAIN);
	if (handle_fds(data, data->cmd_line))
		return(AGAIN);
	if (data->cmds == 1)
		err = exec_single_cmd(data->cmd_line, data->cmd_line->parent, data);
	else
		err = exec_multi_cmds(data->cmd_line, data->cmds, data);
	if (err != 0)
		ft_error("ERROR\n", data);
	return (SUCCESS);	
}
