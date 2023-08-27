#include "minishell.h"

int	handle_input(t_data *data)
{
	data->input = readline("> ");
	if (!data->input)
		ft_error(MALLOC_ERR, NULL);
	add_history(data->input);
	lexer(data);
	if (parser(data))
		return (AGAIN);
	if (cmdfinder(data, data->cmd_line))
		return(1);
	// t_parse *tmp = data->cmd_line;
	// int i = 0;
	// while (tmp->id != 0)
	// {
	// 	printf("id %d,", tmp->id);
	// 	i = 0;
	// 	while (tmp->cmd && tmp->cmd[i])
	// 		printf(" cmd: %s", tmp->cmd[i++]);
	// 	printf("\nin: %s\nout: %s\nheredoc: %s\n",tmp->infile, tmp->outfile, tmp->heredoc);
	// 	tmp++;
	// }
	return (SUCCESS);
}
