#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (error_msg(NULL, NULL, ARGC_ERR, FAIL));
	init_data(&data);
	data.env = copy_envp(&data, envp);
	if (!data.env)
		return (ft_error(MALLOC_ERR, NULL));
	while (1)
	{
		handle_signals(false);
		if (handle_input(&data) == SUCCESS)
			executor(&data);
		ft_cleanup(&data, false);
	}
	return (SUCCESS);
}

