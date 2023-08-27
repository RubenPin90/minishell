#include "minishell.h"

void	init_data(t_data *data)
{
	data->cmds = 0;
	data->paths = NULL;
	data->cmd_line = NULL;
	data->lex = NULL;
	data->env = NULL;
	data->input = NULL;
}

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
		// else 
		// 	if (executer(&data))
		// 		ft_error(NULL, &data);	
		ft_cleanup(&data, false);
	}
	return (0);
}

