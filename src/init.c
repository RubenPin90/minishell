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
