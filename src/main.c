#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (error_msg(NULL, NULL, ARGC_ERR));
	init_data(&data);
	data.env = copy_envp(envp);
	handle_signals(false);
	while (1)
	{
		if (handle_input(&data))
			ft_cleanup(&data, false);
		else
			if (executor(&data))
				ft_cleanup(&data, false);
		ft_cleanup(&data, false);
	}
	return (0);
}

