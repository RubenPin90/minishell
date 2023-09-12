#include "../inc/lexer.h"

// TODO: what should happen when open quotes are found?
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
