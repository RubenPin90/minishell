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
	return (0);
}