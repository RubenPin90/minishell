#include "builtins.h"

int	ft_exit(t_data *data)
{
	ft_printf("exit\n");
	ft_cleanup(data, true);
	exit(0);
	return (SUCCESS);
}