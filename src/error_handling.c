#include "error_handling.h"

int error_msg(char *cmd, char *msg)
{
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(msg, 2);
	}
	else
		ft_putstr_fd(msg, 2);
	return (AGAIN);
}

int	ft_error(char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	if (data)
	{
		ft_cleanup(data, true);
		exit(FAIL);
	}
	return (1);
}
