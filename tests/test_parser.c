
/*#file: test_parser.c
**#descr: Containing functions for testing the parser.
**#funcs:
**- int cmd_counter(t_lexer *lex): Counting cmds from lexer linked list.
**- void free_lexer(t_lexer **lex): Freeing lexer linked list.
**- int parser():
*/
#include "minishell.h"

/*#class: t_parse
**#descr: grouping lexer nodes together into each cmd.
**#prop: -
**#use: -
*/
typedef struct s_parse
{
	char			*cmd_link;
	char			**cmd;
	char			*infile;
	char			*outfile;
	char			*heredoc;
	int				num_redir;
}	t_parse;

/*#fname: cmd_counter
**#descr: Counting commands sent from lexer.
**
**Loops through lexer linked list, increases count
**with each pipe, starting from 1.
**#params: lex - Tokenized input list.
**#return: count - number of commands.
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
	return (count);
}

/*#fname: parser
**#descr: Convertes lexer list to each commands.
**
**n/a
**#params: 
**- *data: general data struct
**- *lex:
**- **cmd_line
**#return: 1 if error; 0 if success.
*/
int	parser(t_data *data, t_lexer *lex, t_parse **cmd_line)
{
	t_lexer	*start;
	int		cmd_size;

	data->cmds = cmd_counter(lex);
	*cmd_line = ft_calloc(sizeof(t_parse *), data->cmds);
	if (!*cmd_line)
		return (1);
	start = lex;
	while (lex)
	{
		if (lex->token == PIPE || lex->next == NULL)
		{
			extract_cmd()
		}
		lex = lex->next;
	}
	return (0);
}

/*#fname: free_lexer
**#descr: destroying & freeing the lexer struct.
**#params: **lex - 2D to be able to set it to NULL.
**#return: void
*/
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
	t_data	data;

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
	if (parser(&data, lex, &cmd_line))
	{
		free_lexer(&lex);
		return (1);
	}
	free_lexer(&lex);
	free(cmd_line);
	return (0);
}


