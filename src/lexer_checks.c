#include "../inc/lexer.h"

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
		// if (*input == '>')
		// 	if (check_out(input))
		// 		return (1);
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
			return (ft_error("Third '>'/'<' found! KO\n", NULL));
		}
		// printf("HEREDOC/APPEND found! OK\n");
		return (0);
	}
	while (*input == ' ')
		input++;
	if (!*input)
	{
		redir = 0;
		return (ft_error("Token at end of line! KO\n", NULL));
	}
	if (*input != '<' && *input != '>' && *input != '|')
	{
		redir = 0;
		return (0);
	}
	redir = 0;
	return (ft_error("Consecutive token found! KO\n", NULL));
}

// int	check_out(char *input)
// {
// 	static int	out;

// 	input++;
// 	if (*input == '>')
// 	{
// 		out++;
// 		if (out >= 2)
// 		{
// 			out = 0;
// 			return (ft_error("Third '>' found! KO\n", NULL));
// 		}
// 		printf("APPEND found! OK\n");
// 		return (0);
// 	}
// 	while (*input == ' ')
// 		input++;
// 	if (!*input)
// 	{
// 		out = 0;
// 		return (ft_error("Token at end of line! KO\n", NULL));
// 	}
// 	if (*input != '<' && *input != '>' && *input != '|')
// 	{
// 		out = 0;
// 		return (0);
// 	}
// 	out = 0;
// 	return (ft_error("Consecutive token found! KO\n", NULL));
// }

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
	return (WORD);
}
