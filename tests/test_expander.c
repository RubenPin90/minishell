#include "minishell.h"

int	find_dsign(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	return (i);
}

void	check_result(t_data *data, char *expected)
{
	t_lexer		*tmp_lst;
	char		*result;
	char		*tmp_str;

	tmp_lst = data->lex;
	result =  NULL; //ft_calloc(sizeof(char), 1);
	while (tmp_lst)
	{
		tmp_str = result;
		if (!result && tmp_lst->i == 0)
			result = ft_strdup(tmp_lst->word);
		else
			result = ft_strjoin_wrapper(result, " ", tmp_lst->word);
		tmp_str = free_null(tmp_str);
		tmp_lst = tmp_lst->next;
	}
	lexer_printer(data->lex, false);
	if (!result || !expected)
		printf("no result or expected\n");
	else if(!strcmp(result, expected))
		printf(GREEN"OK\n"RESET);
	else
		printf(RED"KO\n"RESET);
}

void	print_output(t_data *data)
{
	t_lexer	*tmp = data->lex;

	tmp = data->lex;
	while (tmp)
	{
		printf("%s ", tmp->word);
		tmp = tmp->next;
	}
	printf("\n===\n");
}

int	test_quotes(char *quote, char *expected)
{
	// int		i;
	// char	*value = "aapostol";
	// char	*output;
	extern	char **environ;
	t_word	word;
	t_data	data;

	init_data(&data);
	word.i = 0;
	word.start = word.i;
	data.env = copy_envp(environ);
	data.input = ft_strdup(quote);
	printf("input: %s, expected: %s\n", data.input, expected);
	// i = find_dsign(quote);
	expander(&data, data.input);
	data.lex = create_list(&data, &data.input);
	count_lexlst(data.lex);
	check_result(&data, expected);
	// output = data.lex->word;
	// printf("quote: %s\n"GREEN"expected: %s\n"YELLOW"output: "RESET, quote, expected);
	// print_output(&data);
	// if(!strcmp(output, expected))
	// 	printf(GREEN"OK\n"RESET);
	// else
	// 	printf(RED"KO\n"RESET);
	// free(output);
	return (0);
}

char	*get_user(void)
{
	extern char **environ;
	int			i;
	int			len;
	char		*value;

	i = 0;
	while (environ[i])
	{
		if (!strncmp(environ[i], "USER=", 5))
		{
			len = ft_strlen(environ[i]) - 5;
			value = ft_substr(environ[i], 5, len);
		}
		i++;
	}
	return (value);
}

int	test_expander(char *quote, char *expected)
{
	t_data		data;
	extern char	**environ;

	init_data(&data);
	data.input = ft_strdup(quote);
	data.env = copy_envp(environ);
	printf("input: %s, expected: %s\n", data.input, expected);
	expander(&data, data.input);
	create_list(&data, &data.input);
	count_lexlst(data.lex);
	// printf("data->input: %s\nexpected: %s\n", data.input, expected);
	check_result(&data, expected);
	ft_cleanup(&data, true);
	return (0);
}

int	test_lexer_expander()
{
	char	*user;

	user = get_user();
	printf("user: %s\n", user);
	printf(YELLOW"----------test-list----------\n"RESET);
	test_quotes("hello", "hello");
	test_quotes("\"hello\"", "hello");
	test_quotes("\"hello\" world", "hello world");
	test_quotes("\"hello\"world", "helloworld");
	test_quotes("hello\"world\"", "helloworld");
	test_quotes("\"hello\"\"world\"", "helloworld");
	test_quotes("\"hello\" \"world\"", "hello world");
	printf(YELLOW"----------test-quotes----------\n"RESET);
	test_quotes("\"$USER\"", user);
	test_quotes("'$USER'", "$USER");
	test_quotes("\"'$USER'\"", "'ada'");
	test_quotes("'\"$USER\"'", "\"$USER\"");
	test_quotes("$\"USER\"", "USER");
	test_quotes("$'USER'", "USER");
	test_quotes("\"$'USER'\"", "$'USER'");
	test_quotes("'$\"USER\"'", "$\"USER\"");
	test_quotes("\"$\"USER\"\"", "$USER");
	test_quotes("'$'USER''", "$USER");
	test_quotes("\"\"$USER\"\"", "ada");
	test_quotes("''$USER''", "ada");
	printf(YELLOW"----------test-expander----------\n"RESET);
	test_expander("\"$USER\"", user);
	test_expander("'$USER'", "$USER");
	test_expander("\"'$USER'\"", "'ada'");
	test_expander("'\"$USER\"'", "\"$USER\"");
	test_expander("$\"USER\"", "USER");
	test_expander("$'USER'", "USER");
	test_expander("\"$'USER'\"", "$'USER'");
	test_expander("'$\"USER\"'", "$\"USER\"");
	test_expander("\"$\"USER\"\"", "$USER");
	test_expander("'$'USER''", "$USER");
	test_expander("\"\"$USER\"\"", "ada");
	test_expander("''$USER''", user);
	test_expander("$USER", user);
	test_expander("\"$\"USER", "$USER");
	test_expander("'$'USER", "$USER");
	test_expander("'$USER'", "$USER");
	test_expander("\"$USER\"", user);
	test_expander("$USERR", "");
	test_expander("'$A'\"$USER'ada'\"", "$Aada'ada'");
	test_expander("\"   $    USER\"", "   $    USER");
	test_expander("   $    USER", "$ USER");
	test_expander("$\"$USER\"", user);
	test_expander("\"$\"", "$");
	test_expander("'$'", "$");
	test_expander("\"  $  \"", "  $  ");
	test_expander("$\"\"", "");
	test_expander("$\"abc\"", "abc");
	test_expander("\"$USER\"", user);
	test_expander("'$USER'", "$USER");
	test_expander("\"'$USER'\"", "'ada'");
	test_expander("'\"$USER\"'", "\"$USER\"");
	test_expander("$\"USER\"", "USER");
	test_expander("$'USER'", "USER");
	test_expander("\"$'USER'\"", "$'USER'");
	test_expander("'$\"USER\"'", "$\"USER\"");
	test_expander("\"$\"USER\"\"", "$USER");
	test_expander("'$'USER''", "$USER");
	test_expander("\"\"$USER\"\"", user);
	test_expander("\"$\"abc\"\"", "$abc");
	test_expander("$\"\"", "");
	test_expander("\"\"\"\"$\"\"\"\"", "");
	test_expander("\"$\" \"\"\"\"$\"\"\"\"", "$ ");
	test_expander("\"$hello\" how are you\"$\" \"\"\"\"$\"\"\"\"", " how are you$ ");
	user = free_null(user);
	return (0);
}

// // terminal expected output
// "$USER"		= 	aapostol
// '$USER'		= 	$USER
// "'$USER'"	= 	'aapostol'
// '"$USER"'	= 	"$USER"
// $"USER"		= 	USER //first double quotes
// $'USER'		= 	USER //first single quote
// "$'USER'"	= 	$'USER'
// '$"USER"'	= 	$"USER"
// "$"USER""	= 	$USER //wrong output: "USER"
// '$'USER''	= 	$USER //wrong output: 'USER'
// ""$USER""	=	aapostol //second double quotes
// ''$USER''	=	aapostol //second single quote