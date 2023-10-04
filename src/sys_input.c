#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		ft_exit(data, NULL);
	if (!ft_strlen(data->input))
		return (AGAIN);
	add_history(data->input);
	if (lexer(data))
		return (AGAIN);
	export_check(data, data->lex);
	if (parser(data, data->lex))
		return (AGAIN);
	return (SUCCESS);
}

