
#include "executer.h"




int	exec_single_cmd(t_parse *cmd_line, t_data *data)
{
	if (cmd_line->func)
		(*cmd_line->func)(data);
	else
		execve(cmd_line->cmd[0], cmd_line->cmd, list_to_arr(data, data->env));
	return (SUCCESS);
}

int executer(t_data *data)
{
	int	err;

	err = 0;
	cmd_printer(data);
	//create_pipes(data->cmd_line, data);
	if (data->cmds == 1)
		err = exec_single_cmd(data->cmd_line, data);
	// else
	// 	err = exec_multi_cmds(data->cmd_line, data->cmds, data);
	if (err != 0)
		ft_error("ERROR\n", data);
	return (0);	
}