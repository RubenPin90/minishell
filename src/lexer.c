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

void	lexer(char *input, t_lexer *lex)
{
	create_list(input, lex);
}
