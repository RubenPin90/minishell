
#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		return (1);
	check_buildin(data);
	//lexer(data->input);
	return (0);
}
