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
	if (parser(data))
		return (AGAIN);
	// t_parse *tmp = data->cmd_line;
	// int i = 0;
	// while (tmp->id != 0)
	// {
	// 	printf("id %d,", tmp->id);
	// 	i = 0;
	// 	// printf("lex: %s=%d\n", data->lex->word, data->lex->token);
	// 	while (tmp->cmd && tmp->cmd[i])
	// 		printf(" cmd: %s", tmp->cmd[i++]);
	// 	printf("\nin: %s\nout: %s\nheredoc: %s\n",tmp->infile, tmp->outfile, tmp->heredoc);
	// 	tmp++;
	// }
	if (cmdfinder(data, data->cmd_line))
		return(1);
	return (SUCCESS);
}

