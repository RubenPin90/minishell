#include "minishell.h"

int	test_lexer_list(char *line)
{
	t_data data;
	t_lexer *tmp;

	data.input = line;
	data.lex = NULL;
	data.lex = create_list(&data, &line);
	tmp = data.lex;
	while (tmp)
	{
		printf("%s ", tmp->word);
		fflush(NULL);
		tmp = tmp->next;
	}
	free_lexer(&data.lex);
	return (0);
}

int	test_input(char *line)
{
	t_data data;

	data.lex = NULL;
	data.input = line;
	printf("%s\n", line);
	if (lexer(&data))
	{
		printf(RED"----------EXIT----------\n"RESET);
		free_lexer(&data.lex);
		return (1);
	}
	printf(GREEN"----------INPUT OK----------\n"RESET);
	t_lexer *tmp = data.lex;
	while (tmp)
	{
		printf("%s(=%d) ", tmp->word, tmp->token);
		printf("\n");
		tmp = tmp->next;
	}
	free_lexer(&data.lex);
	return (0);
}

int	test_lexer()
{
	// printf(YELLOW"----------test-lexer OK----------\n"RESET);
	// test_input("a | b   ");
	// test_input("hello > world");
	// test_input("hello < world");
	// test_input("hello | world");
	// test_input("hello >> world");
	// test_input("hello << world");
	// test_input("<< onlyheredoc");
	// test_input("hello |> world");
	// test_input("echo hello >file1 > file2");
	// test_input("cat << EOF >file1 > file2");
	// test_input("cat << EOF hello >file1 > file2");
	// printf(YELLOW"----------test-lexer KO----------\n"RESET);
	// test_input("hello | | world");
	// test_input("hello || world");
	// test_input("hello <<< world");
	// test_input("hello >>> world");
	// test_input("hello|world|");
	// test_input("hello >| world");

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
