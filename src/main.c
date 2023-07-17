#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data				data;

	(void)argv;
	if (argc != 1)
		return (1);
	data.env = copy_envp(envp);
	//handle_signals();
	while (1)
	{
		if (handle_input(&data))
			break ;
			//save_data_history();
			//lexer();
			//parser();
			//expander();
			//executer();
			//free;
	}
	return (0);
}

