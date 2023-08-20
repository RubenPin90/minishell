#include "../inc/lexer.h"

void	add_node(char *input, int start, int len, t_lexer *lex)
{
	t_lexer	*node;

	node = new_lexer_node(ft_substr(input, start, len), 0);
	lexer_addback(&lex, node);
}

// reads through input string and copies every word/token into a node
t_lexer	*create_list(char *input, t_lexer *lex)
{
	int	i;
	int	start;
	int	len;

	i = 0;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		start = i;
		while (input[i] && input[i] != ' ')
			i++;
		len = i - start;
		add_node(input, start, len, lex);
		i++;
	}
	printf("\n");
	return (lex);
}

int	check_out(char *input)
{
	static int	out;

	input++;
	if (*input == '>')
	{
		out++;
		if (out >= 2)
		{
			out = 0;
			return (ft_error("Third '>' found! KO\n", NULL));
		}
		printf("APPEND found! OK\n");
		return (0);
	}
	while (*input == ' ')
		input++;
	if (!*input)
	{
		out = 0;
		return (ft_error("Token at end of line! KO\n", NULL));
	}
	if (*input != '<' && *input != '>' && *input != '|')
	{
		out = 0;
		return (0);
	}
	out = 0;
	return (ft_error("Consecutive token found! KO\n", NULL));
}

int	check_in(char *input)
{
	static int	in;

	input++;
	if (*input == '<')
	{
		in++;
		if (in >= 2)
		{
			in = 0;
			return (ft_error("Third '>' found! KO\n", NULL));
		}
		printf("HEREDOC found! OK\n");
		return (0);
	}
	while (*input == ' ')
		input++;
	if (!*input)
	{
		in = 0;
		return (ft_error("Token at end of line! KO\n", NULL));
	}
	if (*input != '<' && *input != '>' && *input != '|')
	{
		in = 0;
		return (0);
	}
	in = 0;
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

int	check_token(char *input)
{
	while (*input)
	{
		if (*input == '|')
			if (check_pipe(input))
				return (1);
		if (*input == '<')
			if (check_in(input))
				return (1);
		if (*input == '>')
			if (check_out(input))
				return (1);
		input++;
	}
	return (0);
}

int	lexer(char *input, t_lexer *lex)
{
	if (check_quotes(input) || check_token(input))
		return (1);
	create_list(input, lex);
	return (0);
}
