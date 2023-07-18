#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data				data;

	(void)argv;
	if (argc != 1)
		return (ft_error(ARGC_ERR, NULL));
	data.env = copy_envp(envp);
	//handle_signals();
	while (1)
	{
		if (handle_input(&data))
			return (ft_error(NULL, &data));
			//lexer();
			//parser();
			//expander();
			//executer();
			//free;
	}
	return (0);
}

