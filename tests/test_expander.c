#include "minishell.h"

int	expand_quotes(char *quote, char *result)
{
	printf("%s = %s\n", quote, result);
	return (0);
}

int	test_expander()
{
	printf(YELLOW"----------test-expander----------\n"RESET);
	expand_quotes(GREEN"\"$USER\"", "aapostol"RESET);
	expand_quotes(YELLOW"'$USER'", "$USER");
	expand_quotes(GREEN"\"'$USER'\"", "'aapostol'"RESET);
	expand_quotes(YELLOW"'\"$USER\"'", "\"$USER\""RESET);
	expand_quotes("$\"USER\"", "USER");
	expand_quotes("$'USER'", "USER");
	expand_quotes("\"$'USER'\"", "$'USER'");
	expand_quotes(YELLOW"'$\"USER\"'", "$\"USER\""RESET);
	expand_quotes("\"$\"USER\"\"", "$USER");
	expand_quotes("'$'USER''", "$USER");
	expand_quotes(GREEN"\"$USER\"", "aapostol"RESET);
	expand_quotes(GREEN"''$USER''", "aapostol"RESET);
	return (0);
}

// // terminal expected output
"$USER"		= 	aapostol
'$USER'		= 	$USER
"'$USER'"	= 	'aapostol'
'"$USER"'	= 	"$USER"
$"USER"		= 	USER
$'USER'		= 	USER
"$'USER'"	= 	$'USER'
'$"USER"'	= 	$"USER"
"$"USER""	= 	$USER
'$'USER''	= 	$USER
""$USER""	=	aapostol
''$USER''	=	aapostol