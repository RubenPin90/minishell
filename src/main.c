#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data				data;

	(void)argv;
	if (argc != 1)
		ft_error(ARGC_ERR, NULL);
	data.env = copy_envp(envp);
	data.lex = NULL;
	//handle_signals();
	while (1)
	{
		if (handle_input(&data))
			ft_error(NULL, &data);
		if (executer(&data))
			ft_error(NULL, &data);	
		ft_cleanup(&data, false);
		// free_lexer(&data.lex);
		// data.cmd_line = free_parser(data.cmd_line);
	// 		//parser();
	// 		//expander();
	// 		//executer();
	}
	return (0);
}

