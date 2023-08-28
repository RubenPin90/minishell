/**
 * @file lexer.c
 * @brief Create lex list
 * 
 */

#include "../inc/lexer.h"

/**
 * @brief Add a new node to the end of the list
 * 
 * Copies a word from the input string into 
 * @param data 
 * @param start 
 * @param len 
 * @param type 
 */
void	add_node(t_data *data, char *input, t_word *word)
{
	t_lexer	*node;

	if (word->type == PIPE)
		word->len = 1;
	node = new_lexer_node(ft_substr(input, word->start, word->len), \
			word->type);
	if (!node)
		return ;
	lexer_addback(&data->lex, node);
}

// reads through input string and copies every word/token into a node
t_lexer	*create_list(t_data *data, char **datainput)
{
	t_word	word;
	char	*input;

	input = *datainput;
	word.i = 0;
	word.start = 0;
	while (input[word.i])
	{
		skip_space(input, &word.i);
		word.type = check_type(input, &word.i);
		if (word.type == STOP)
			break ;
		skip_space(input, &word.i);
		printf("start: %d\n", word.start);
		input = get_word(data, input, &word);
		printf("len: %d\n", word.len);
		add_node(data, input, &word);
		if (word.type == PIPE)
			word.i++;
	}
	*datainput = input;
	return (data->lex);
}

int	lexer(t_data *data)
{
	if (check_quotes(data->input) || check_token(data->input))
		return (1);
	create_list(data, &data->input);
	printf("data->input: %s\n", data->input);
///
	t_lexer *tmp = data->lex;
	printf("input str in lexer.c: %s\n", data->input);
	while (tmp)
	{
		printf("nodes in lex: %s=%d ", tmp->word, tmp->token);
		tmp = tmp->next;
	}
	printf("\n");
///
	return (0);
}
