#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		ft_error("test", NULL);
	if (!ft_strlen(data->input))
		return (AGAIN);
	add_history(data->input);
	lexer(data);
	if (parser(data, data->lex))
		return (AGAIN);
	return (SUCCESS);
}

