#include "minishell.h"

int	test_lexer_list(char *line)
{
	t_lexer	*lex;
	t_lexer *tmp;

	lex = NULL;
	lex = create_list(line, lex);
	tmp = lex;
	while (tmp)
	{
		printf("%s ", tmp->word);
		tmp = tmp->next;
	}
	return (0);
}

int	test_input(char *line)
{
	printf("%s\n", line);
	if (lexer(line, NULL))
	{
		printf(RED"----------EXIT----------\n"RESET);
		return (1);
	}
	printf(GREEN"----------INPUT OK----------\n"RESET);
	return (0);
}

int	test_lexer()
{
	printf(YELLOW"----------test-lexer OK----------\n"RESET);
	test_input("hello world");
	test_input("hello > world");
	test_input("hello < world");
	test_input("hello | world");
	test_input("hello >> world");
	test_input("hello << world");
	test_input("<< onlyheredoc");
	test_input("hello |> world");
	test_input("echo hello >file1 > file2");
	test_input("cat << EOF >file1 > file2");
	test_input("cat << EOF hello >file1 > file2");
	printf(YELLOW"----------test-lexer KO----------\n"RESET);
	test_input("hello | | world");
	test_input("hello || world");
	test_input("hello <<< world");
	test_input("hello >>> world");
	test_input("hello|world|");
	test_input("hello >| world");

	printf(YELLOW"----------test-lexer-list----------\n"RESET);
	test_lexer_list("hello world");
	test_lexer_list("hello > world");
	test_lexer_list("hello < world");
	test_lexer_list("hello | world");
	test_lexer_list("hello >> world");
	test_lexer_list("hello << world");
	test_lexer_list("hello |> world");
	test_lexer_list("echo hello >file1 > file2");
	test_lexer_list("cat << EOF >file1 > file2");
	test_lexer_list("cat << EOF hello >file1 > file2");
	return (0);
}
