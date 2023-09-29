#include "builtin.h"

int	check_exit(char *arg)
{
	int i;

	i = 0;
	if (!arg)
		return (SUCCESS);
	if (arg[i] == '\0')
		return (FAIL);
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
	int num_args;
	int ex_code;

	ex_code = 0;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	if (cmd)
	{
		num_args = ft_arrlen(cmd->cmd);
		if (num_args > 2)
		{
			error_msg("exit", NULL, ARG_ERR);
			ex_code = 1;
		}
		else if (check_exit(cmd->cmd[1]))
		{
			error_msg("exit", cmd->cmd[1], NUM_ERR);
			ex_code = 1;
		}
		else if (num_args == 2)
			ex_code = ft_atoi(cmd->cmd[1]);
	}
	ft_cleanup(data, true);
	exit(ex_code);
	return (SUCCESS);
}
