#include "minishell.h"

int	handle_input(t_data *data)
{
	data->lex = NULL;
	data->input = readline("> ");
	if (!data->input)
		ft_error(MALLOC_ERR, data);
	add_history(data->input);
	check_buildin(data);
	lexer(data);
	free(data->input);
	return (SUCCESS);
}
