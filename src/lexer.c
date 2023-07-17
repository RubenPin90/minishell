
#include "../inc/lexer.h"

// reads through input string and copies every word/token into a list node
void	lexer(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		printf("%c", input[i++]);
	}
	printf("\n");
}
