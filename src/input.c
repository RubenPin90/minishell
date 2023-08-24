#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		ft_error(MALLOC_ERR, data);
	add_history(data->input);
	check_buildin(data);
	lexer(data);
	parser(data);
	cmdfinder(data, data->cmd_line);
	t_parse *tmp = data->cmd_line;
	int i = 0;
	while (tmp->id != 0)
	{
		printf("id %d,", tmp->id);
		i = 0;
		while (tmp->cmd[i])
			printf(" cmd: %s", tmp->cmd[i++]);
		printf("\nin: %s\nout: %s\nheredoc: %s\n",tmp->infile, tmp->outfile, tmp->heredoc);
		tmp++;
	}
	return (SUCCESS);
}
