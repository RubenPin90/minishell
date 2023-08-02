#include "minishell.h"

typedef struct s_parse
{
	char			*cmd_link;
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*heredoc;
}	t_parse;


/*#fname: cmd_counter
**#descr: iterating through lex to count \
**        by counting pipes.
**#params: lex - converted readline string
**#return: number of commands
*/
int cmd_counter(t_lexer *lex)
{
	int count;

	count = 1;
	while (lex)
	{
		if (lex->token == 1)
			count++;
		lex = lex->next;
	}
}


int	parser(t_lexer *lex, t_parse **cmd_line)
{
	t_lexer	*tmp;
	int		cmds;
	int		cmd_size;

	cmds = cmd_counter(lex);
	*cmd_line = ft_calloc(sizeof(t_parse *), cmds);
	if (!*cmd_line)
		return (1);
	
	while (lex)
	{
		if (lex->next && lex->next->token != PIPE)
		{

		}
		if (lex->token == PIPE)
			break ;
		lex = lex->next;
	}
	return (0);
}

void	free_lexer(t_lexer **lex)
{
	t_lexer	*tmp;

	tmp = *lex;
	while (*lex)
	{
		tmp = (*lex)->next;
		free(*lex);
		*lex = tmp;
	}
	*lex = NULL;
}

int	test_parser(void)
{
	t_lexer	*lex;
	t_lexer	*start;
	t_parse	*cmd_line;

	lex = NULL;
	lexer_addback(&lex, new_lexer_node("ls", 0));
	lexer_addback(&lex, new_lexer_node("-la", 0));
	lexer_addback(&lex, new_lexer_node(0, 1));
	lexer_addback(&lex, new_lexer_node("wc", 0));
	lexer_addback(&lex, new_lexer_node("-l", 0));

	start = lex;
	while (lex)
	{
		printf("%s ", lex->word);
		lex = lex->next;
	}
	lex = start;
	if (parser(lex, &cmd_line))
	{
		free_lexer(&lex);
		return (1);
	}
	free_lexer(&lex);
	free(cmd_line);
	return (0);
}


