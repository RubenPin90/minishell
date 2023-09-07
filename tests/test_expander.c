#include "minishell.h"

int	find_dsign(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	return (i);
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
	printf("\n");
}

int	test_quotes(char *quote, char *expected)
{
	// int		i;
	// char	*value = "aapostol";
	char	*output;
	t_word	word;
	t_data	data;

	init_data(&data);
	word.i = 0;
	word.start = word.i;
	// printf("before expander-----\nquote: %s, expected: %s\n", quote, expected);
	// i = find_dsign(quote);
	data.lex = create_list(&data, &quote);
	count_lexlst(data.lex);
	output = data.lex->word;
	printf("quote: %s\nexpected: %s\noutput: ", quote, expected);
	print_output(&data);
	if(!strcmp(output, expected))
		printf(GREEN"OK\n"RESET);
	else
		printf(RED"KO\n"RESET);
	free(output);
	return (0);
}

int	test_expander()
{
	// printf(YELLOW"----------test-list----------\n"RESET);
	// test_quotes("hello", "hello");
	// test_quotes("\"hello\"", "hello");
	// test_quotes("\"hello\" world", "hello world");
	// test_quotes("\"hello\"world", "helloworld");
	// test_quotes("\"hello\"\"world\"", "helloworld");
	// test_quotes("\"hello\" \"world\"", "hello world");
	printf(YELLOW"----------test-expander----------\n"RESET);
	test_quotes("\"$USER\"", "aapostol");
	test_quotes("'$USER'", "$USER");
	test_quotes("\"'$USER'\"", "'aapostol'");
	test_quotes("'\"$USER\"'", "\"$USER\"");
	test_quotes("$\"USER\"", "USER");  
	test_quotes("$'USER'", "USER");
	test_quotes("\"$'USER'\"", "$'USER'");
	test_quotes("'$\"USER\"'", "$\"USER\"");
	test_quotes("\"$\"USER\"\"", "$USER");
	test_quotes("'$'USER''", "$USER");
	test_quotes("\"\"$USER\"\"", "aapostol");
	test_quotes("''$USER''", "aapostol");
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