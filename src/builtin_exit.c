#include "builtin.h"

int	ft_exit(t_data *data, t_parse *cmd)
{
	int num_args;
	int ex_code;

	ex_code = 0;
	if (!cmd)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	else
	{
		num_args = ft_arrlen(cmd->cmd);
		if (num_args > 2)
		{
			error_msg("exit", ARG_ERR);
			ex_code = 1;
		}
		if (num_args == 2)
			define_ex_code(&ex_code);
	}
	ft_cleanup(data, true);
	exit(ex_code);
	return (SUCCESS);
}
