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
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			if (check_pipe(input, i))
				return (1);
		if (input[i] == '<' || input[i] == '>')
			if (check_redir(input, i))
				return (1);
		input++;
	}
	return (0);
}

int	check_redir(char *input, int i)
{
	static int	redir;

	if (input[i] == '>' && input[i + 1] == '|')
		return (0);
	i++;
	if (input[i] == '<' || input[i] == '>')
	{
		redir++;
		if (redir >= 2)
		{
			redir = 0;
			return (error_msg(NULL, NULL, TOKEN_ERR, AGAIN));
		}
		return (0);
	}
	redir = 0;
	while (input[i] == ' ' || (input[i] >= 9 && input[i] <= 13))
		i++;
	if (!input[i] || input[i] == '<' || input[i] == '>' || input[i] == '|')
		return (error_msg(NULL, NULL, TOKEN_ERR, AGAIN));
	return (0);
}

int	check_pipe(char *input, int i)
{
	i++;
	while (input[i] == ' ')
		i++;
	if (!input[i] || input[i] == '|')
		return (error_msg(NULL, NULL, TOKEN_ERR, AGAIN));
	return (0);
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
		if (input[*i] == '|')
			(*i)++;
		return (OUTPUT);
	}
	if (input[*i] == '|')
		return (PIPE);
	if (input[*i])
		return (WORD);
	return (STOP);
}
