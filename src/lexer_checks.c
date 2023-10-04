#include "../inc/lexer.h"

int	check_quotes(char *str)
{
	int		i;
	bool	doubles;
	bool	singles;

	i = 0;
	doubles = false;
	singles = false;
	while (str[i])
	{
		if (str[i] == '"')
			toggle_quotes(&doubles, &singles);
		if (str[i] == '\'')
			toggle_quotes(&singles, &doubles);
		i++;
	}
	if (doubles == true || singles == true)
		return (1);
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
			return (error_msg(NULL, NULL, TOKEN_ERR));
		}
		return (0);
	}
	redir = 0;
	while (*input == ' ')
		input++;
	// if (!*input)
	// 	return (error_msg(NULL, NULL, TOKEN_ERR));
	if (*input != '<' && *input != '>' && *input != '|')
		return (0);
	return (error_msg(NULL, NULL, TOKEN_ERR));
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
