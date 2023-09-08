#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		ft_error(MALLOC_ERR, NULL);
	if (!ft_strlen(data->input))
		return (AGAIN);
	add_history(data->input);
	lexer(data);
	if (parser(data, data->lex))
		return (AGAIN);
	if (cmdfinder(data, data->cmd_line))
		return(FAIL);
	return (SUCCESS);
}

