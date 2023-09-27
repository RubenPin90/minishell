#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		ft_error(ARGC_ERR, NULL);
	init_data(&data);
	data.env = copy_envp(envp);
	//handle_signals();
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

