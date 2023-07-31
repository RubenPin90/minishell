#include "minishell.h"

void	ft_wrapper(char *line)
{
	t_lexer	*lex;

	lex = NULL;
	lexer(line, lex);
	while (lex)
	{
		printf("%s", lex->word);
		lex = lex->next;
	}
	free(lex);
}

int	test_lexer(void)
{
	printf("----test-lexer-------");
	ft_wrapper("ls -la");
	return (0);
}

int	main(void)
{
//	test_lexer();
	test_parser();
//	test_env();
	return (0);
}