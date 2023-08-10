/*#file: test_parser.c
**#descr: Containing functions for creating the parser.
*/
#include "minishell.h"

/*colors*/
# define RESET "\e[0m"
# define RED "\e[0;31m"
# define GREEN "\e[0;32m"
# define YELLOW "\e[0;33m"
# define BLUE "\e[0;34m"
# define PINK "\e[0;35m"


void set_prev(t_lexer **lex)
{
	t_lexer *tmp;
	t_lexer *prev;

	tmp = *lex;
	prev = NULL;
	while(tmp)
	{
		tmp->prev = prev;
		prev = tmp;
		tmp = tmp->next;
	}
}

void count_lexlst(t_lexer **lex)
{
	t_lexer *tmp;
	int		i;

	i = 0;
	tmp = *lex;
	while (tmp)
	{
		tmp->i = i;
		tmp = tmp->next;
		i++;
	}
}

void create_lex(t_lexer **lex, int i)
{
	if (i == 0)
	{
		lexer_addback(lex, new_lexer_node("ls", 0));
		lexer_addback(lex, new_lexer_node("-la", 0));
		lexer_addback(lex, new_lexer_node(0, 1));
		lexer_addback(lex, new_lexer_node("wc", 0));
		lexer_addback(lex, new_lexer_node("-l", 0));
	}
	if (i == 1)
	{
		lexer_addback(lex, new_lexer_node("echo", 0));
		lexer_addback(lex, new_lexer_node("hello", 0));
		lexer_addback(lex, new_lexer_node("file1", 3));
		lexer_addback(lex, new_lexer_node("file2", 3));
	}
	if (i == 2)
	{
		lexer_addback(lex, new_lexer_node("file1", 2));
		lexer_addback(lex, new_lexer_node("cat", 0));
		lexer_addback(lex, new_lexer_node(0, 1));
		lexer_addback(lex, new_lexer_node("grep", 0));
		lexer_addback(lex, new_lexer_node("ein", 0));
		lexer_addback(lex, new_lexer_node(0, 1));
		lexer_addback(lex, new_lexer_node("wc", 0));
		lexer_addback(lex, new_lexer_node("-l", 0));
	}
	if (i == 3)
	{
		lexer_addback(lex, new_lexer_node("cat", 0));
		lexer_addback(lex, new_lexer_node("EOF", 5));
		lexer_addback(lex, new_lexer_node("file1", 3));
		lexer_addback(lex, new_lexer_node("file2", 3));
		lexer_addback(lex, new_lexer_node("file3", 3));
	}
}

int cmd_creator(char *str, int *i)
{
	t_lexer	*start;
	t_parse	*cmd_line;
	t_data	data;
	t_lexer	*lex;

	lex = NULL;
	printf("%s %d\n", str, *i);
	create_lex(&lex, *i);
	count_lexlst(&lex);
	set_prev(&lex);
	start = lex;
	while (lex)
	{
		printf("lex->i: %d lex->word: %s lex->token: %d\n", lex->i, lex->word, lex->token);
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
	(*i)++;
	return(0);
}


int	test_parser(void)
{
	int i;

	i = 0;
	printf("\n%s--------TEST 1---------%s\n", YELLOW, RESET);
	cmd_creator("ls -la | wc -l", &i);
	printf("\n%s--------TEST 2---------%s\n", YELLOW, RESET);
	cmd_creator("echo hello > file1 > file2", &i);
	printf("\n%s--------TEST 3---------%s\n", YELLOW, RESET);
	cmd_creator("< file1 cat | grep ein | wc -l", &i);
	printf("\n%s--------TEST 4---------%s\n", YELLOW, RESET);
	cmd_creator("cat << EOF > file1 > file2 > file3", &i);
	return (0);
}


