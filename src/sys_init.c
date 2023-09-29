#include "minishell.h"

void	init_data(t_data *data)
{
	data->cmds = 0;
	data->paths = NULL;
	data->cmd_line = NULL;
	data->lex = NULL;
	data->env = NULL;
	data->env_arr = NULL;
	data->input = NULL;
	data->exp_lst = NULL;
	data->quoted = false;
	data->expand = true;
	data->word = NULL;
	data->excode = 0;
}
