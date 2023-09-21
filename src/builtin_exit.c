#include "builtin.h"

int	ft_exit(t_data *data, t_parse *cmd)
{
	ft_putstr_fd(cmd->cmd[0], STDOUT_FILENO);
	ft_cleanup(data, true);
	exit(0);
	return (SUCCESS);
}