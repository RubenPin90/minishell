/**
 * @file lexer.c
 * @brief 
 * 
 */

#include "../inc/lexer.h"

void	add_node(t_data *data, int start, int len, int type)
{
	t_lexer	*node;

	node = new_lexer_node(ft_substr(data->input, start, len), type);
	if (!node)
		return ;
	lexer_addback(&data->lex, node);
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

// reads through input string and copies every word/token into a node
t_lexer	*create_list(t_data *data, char *input)
{
	int		i;
	int		start;
	int		len;
	t_lexer	*tmp;
	int		type;

	i = 0;
	type = -1;
	while (input[i])
	{
		while (input[i] == ' ')
			i++;
		// printf("%c=%d ", input[i], i);
		type = check_type(input, &i);
		if (type == PIPE)
		{
			add_node(data, i, 1, PIPE);
			i++;
		}
		else
		{
			// printf("type: %d\n", type);
			while (input[i] == ' ')
				i++;
			start = i;
			while (input[i] && input[i] != ' ' && input[i] != '>' && \
					input[i] != '<' && input[i] != '|')
				i++;
			len = i - start;
			add_node(data, start, len, type);
			if (input[i] && input[i] == ' ')
				i++;
		}
	}
	// printf("i: %d\n", i);
	tmp = data->lex;
	while (tmp)
	{
		printf("%s=%d ", tmp->word, tmp->token);
		fflush(NULL);
		tmp = tmp->next;
	}
	printf("\n");
	return (data->lex);
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

int	lexer(t_data *data)
{
	// data->lex = NULL;
	if (check_quotes(data->input) || check_token(data->input))
		return (1);
	create_list(data, data->input);
	return (0);
}
