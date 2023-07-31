#include "minishell.h"

typedef struct s_parse
{
	char 			*cmd_link;
	char 			*cmd;
	char 			*heredoc;
	struct s_parse	*next;
}	t_parse;



int	test_parser()
{
	t_lexer	*lex;
	t_lexer *start;

	lex = NULL;
	lexer_addback(&lex, new_lexer_node("ls", 0));
	lexer_addback(&lex, new_lexer_node("-la", 0));
	lexer_addback(&lex, new_lexer_node(0, 1));

	start = lex;
	while (lex->token != 1 && lex)
	{
		printf("%s ", lex->word);
		lex = lex->next;
	}
	return (0);
}


