#include "../inc/lexer.h"

int	check_quotes(t_data *data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (data->doubles == false && data->singles == false)
				data->doubles = true;
			else
				data->doubles = false;
		}
		if (str[i] == '\'')
		{
			if (data->singles == false && data->doubles == false)
				data->singles = true;
			else
				data->singles = false;
		}
		i++;
	}
	if (data->doubles == true || data->singles == true)
	{
		data->excode = 2;
		return (1);
	}
	return (0);
}

int	check_token(char *input)
{
	while (*input)
	{
		if (*input == '|')
			if (check_pipe(input))
				return (1);
		if (*input == '<' || *input == '>')
			if (check_redir(input))
				return (1);
		input++;
	}
	return (0);
}

int	check_redir(char *input)
{
	static int	redir;

	input++;
	if (*input == '<' || *input == '>')
	{
		redir++;
		if (redir >= 2)
		{
			redir = 0;
			return (ft_error("Third token found! KO\n", NULL));
		}
		// printf("HEREDOC/APPEND found! OK\n");
		return (0);
	}
	redir = 0;
	while (*input == ' ')
		input++;
	if (!*input)
		return (ft_error("Token at end of line! KO\n", NULL));
	if (*input != '<' && *input != '>' && *input != '|')
		return (0);
	return (ft_error("Consecutive token found! KO\n", NULL));
}

int	check_pipe(char *input)
{
	input++;
	while (*input == ' ')
		input++;
	if (!*input)
		return (ft_error("Token at end of line! KO\n", NULL));
	if (*input != '|')
		return (0);
	return (ft_error("Consecutive pipe found! KO\n", NULL));
}

int	check_type(char *input, int *i)
{
	if (input[*i] == '<')
	{
		(*i)++;
		if (input[*i] == '<')
		{
			(*i)++;
			return (HEREDOC);
		}
		return (INPUT);
	}
	if (input[*i] == '>')
	{
		(*i)++;
		if (input[*i] == '>')
		{
			(*i)++;
			return (APPEND);
		}
		return (OUTPUT);
	}
	if (input[*i] == '|')
		return (PIPE);
	if (input[*i])
		return (WORD);
	return (STOP);
}
