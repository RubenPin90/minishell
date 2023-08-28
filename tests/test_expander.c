#include "minishell.h"

int	find_dsign(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '$')
		i++;
	return (i);
}

int	expand_quotes(char *quote, char *expected)
{
	int		i;
	// char	*value = "aapostol";
	char	*output;
	t_word	word;
	t_data	data;

	init_data(&data);
	word.i = 0;
	word.quoted = false;
	word.start = word.i;
	// printf("before expander-----\nquote: %s, expected: %s\n", quote, expected);
	i = find_dsign(quote);
	data.lex = create_list(&data, &quote);
	output = data.lex->word;
	printf("quote: %s, output: %s, expected: %s\n", quote, output, expected);
	if(!strcmp(output, expected))
		printf(GREEN"OK\n"RESET);
	else
		printf(RED"KO\n"RESET);
	free(output);
	return (0);
}

int	test_expander()
{
	printf(YELLOW"----------test-expander----------\n"RESET);
	expand_quotes("\"$USER\"", "aapostol");
	expand_quotes("'$USER'", "$USER");
	expand_quotes("\"'$USER'\"", "'aapostol'");
	expand_quotes("'\"$USER\"'", "\"$USER\"");
	expand_quotes("$\"USER\"", "USER");
	expand_quotes("$'USER'", "USER");
	expand_quotes("\"$'USER'\"", "$'USER'");
	expand_quotes("'$\"USER\"'", "$\"USER\"");
	expand_quotes("\"$\"USER\"\"", "$USER");
	expand_quotes("'$'USER''", "$USER");
	expand_quotes("\"\"$USER\"\"", "aapostol");
	expand_quotes("''$USER''", "aapostol");
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