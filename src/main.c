#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (error_msg(NULL, NULL, ARGC_ERR, FAIL));
	init_data(&data);
	data.env = copy_envp(envp);
	while (1)
	{
		handle_signals(false);
		if (handle_input(&data) == SUCCESS)
			executor(&data);
		ft_cleanup(&data, false);
	}
	return (0);
}
