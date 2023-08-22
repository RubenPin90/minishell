#include "minishell.h"

int	check_quotes(char *str)
{
	int		i;
	bool	open_doubles;
	bool	open_singles;

	i = 0;
	open_doubles = false;
	open_singles = false;
	while (str[i])
	{
		if (str[i] == 34)
		{
			if (open_doubles == false && open_singles == false)
				open_doubles = true;
			else
				open_doubles = false;
		}
		if (str[i] == 39)
		{
			if (open_singles == false && open_doubles == false)
				open_singles = true;
			else
				open_singles = false;
		}
		i++;
	}
	if (open_doubles == true)
	{
		printf("Open double quotes!\n");
		return (1);
	}
	if (open_singles == true)
	{
		printf("Open single quotes!\n");
		return (1);
	}
	return (0);
}

int	handle_input(t_data *data)
{
	// t_lexer	lex;

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
