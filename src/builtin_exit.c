#include "builtin.h"

int	ft_exit(t_data *data, t_parse *cmd)
{
	(void)cmd;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_cleanup(data, true);
	exit(0);
	return (SUCCESS);
}
