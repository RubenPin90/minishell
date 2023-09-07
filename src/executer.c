
#include "executer.h"
#include <sys/wait.h>

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

int	exec_binary(t_data *data, t_parse *cmd, char *cmdpath)
{
	cmd->pid = fork();
	if (cmd->pid == 0)
		execve(cmdpath, cmd->cmd, data->env_arr);
	return (SUCCESS);
}

int	exec_builtin(t_data *data, t_parse *cmd, bool parent)
{
	if (parent == true)
	{
		if(cmd->func(data))
			return (FAIL);
	}
	else
	{
		cmd->pid = fork();
		if (cmd->pid == 0)
		{
			cmd->func(data);
			exit(0);
		}
	}
	return(SUCCESS);
}

int	exec_single_cmd(t_parse *cmd, bool check, t_data *data)
{
	int		status;

	if (cmd->func)
		exec_builtin(data, cmd, check);
	else
		exec_binary(data, cmd, cmd->cmd_path);
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
		if (cmd_line->func)
			exec_builtin(data, cmd_line, false);
		else
			exec_binary(data, cmd_line, cmd_line->cmd_path);
		cmd_line++;
	}
	while (tmp->id != 0)
	{
		waitpid(tmp->pid, &status, 0);
		tmp++;
	}
	return (SUCCESS);
}

int	handle_fds(t_parse *cmd)
{
	(void)cmd;
	// while (cmd->id != 0)
	// {
	// 	if (cmd->infile)
	// 	{
	// 		here_check = ft_strncmp("heredoc", cmd->infile, 8);
	// 		if (here_check)
	// 		{
	// 			cmd->fd_in = open(cmd->infile, O_RDONLY);
	// 			if (!cmd->fd_in)
	// 				return (error_msg(cmd->infile, FD_NONEX_ERR));
	// 		}
	// 		else
	// 			break ;
	// 	}
	// 	if (cmd->outfile)
	// 	{
	// 		if (cmd->append)
	// 			cmd->fd_out = open(cmd->outfile, O_RDWR | O_APPEND);
	// 		else
	// 			cmd->fd_out = open(cmd->outfile, O_RDWR | O_TRUNC);
	// 		if (!cmd->fd_out)
	// 			return (error_msg(cmd->outfile, FD_ACCESS_ERR));
	// 	}
	// 	cmd++;
	// }
	return (SUCCESS);
}


int executer(t_data *data)
{
	// int	err;

	// err = 0;
	printf("\n_______EXECUTOR:\n\n");
	cmd_printer(data);
	// data->env_arr = list_to_arr(data, data->env);
	// if (handle_fds(data->cmd_line))
	// 	return(AGAIN);
	// if (data->cmds == 1)
	// 	err = exec_single_cmd(data->cmd_line, data->cmd_line->parent, data);
	// else
	// 	err = exec_multi_cmds(data->cmd_line, data->cmds, data);
	// if (err != 0)
	// 	ft_error("ERROR\n", data);
	return (0);	
}