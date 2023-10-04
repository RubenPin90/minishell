#include "error_handling.h"

int error_msg(char *cmd, char *arg, char *msg, int ret)
{
	ft_putstr_fd("minishell: ", 2);
	if (cmd)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": ", 2);
		if (arg)
		{
			ft_putstr_fd(arg, 2);
			ft_putstr_fd(": ", 2);
		}
		ft_putendl_fd(msg, 2);
	}
	else
		ft_putendl_fd(msg, 2);
	return (ret);
}

int	ft_error(char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	if (data)
		ft_cleanup(data, true);
	return (1);
}

void	switch_cmd_status(t_parse *cmd_line, bool *execute, t_status status)
{
	*execute = false;
	cmd_line->exstatus = status; 
}
