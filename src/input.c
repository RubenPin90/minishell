#include "minishell.h"

void	check_quotes(char *str)
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
		printf("Open double quotes!\n");
	if (open_singles == true)
		printf("Open single quotes!\n");
}

int	handle_input(t_data *data)
{
	t_lexer	lex;

	data->input = readline("> ");
	if (!data->input)
		return (ft_error(MALLOC_ERR, NULL));
	add_history(data->input);
	check_quotes(data->input);
	lexer(data->input, &lex);
	check_buildin(data);
	//lexer(data->input);
	return (0);
}
