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
void	add_node(t_data *data, char *lst_word, t_word *word)
{
	t_lexer	*node;

	if (word->type == PIPE)
		word->len = 1;
	node = new_lexer_node(lst_word, word->type);
	if (!node)
		return ;
	lexer_addback(&data->lex, node);
}

// reads through input string and copies every word/token into a node
t_lexer	*create_list(t_data *data, char **datainput)
{
	char	*input;
	char	*lst_word;
	t_word	*word;

	input = *datainput;
	data->word = ft_calloc(sizeof(t_word), 1); // init with 0
	word = data->word;
	while (input[word->i])
	{
		skip_space(input, &word->i);
		word->type = check_type(input, &(word->i));
		if (word->type == STOP)
			break ;
		skip_space(input, &(word->i));
		// printf("start: %d\n", word->start);
		lst_word = get_word(data, input, word);
		// if (!lst_word)
		// 	break ;
		printf("lst_word: %s\n", lst_word);
		add_node(data, lst_word, word);
		printf("lex: %s=%d\n", data->lex->word, data->lex->token);
		if (word->type == PIPE)
			word->i++;
	}
	*datainput = input;
	return (data->lex);
}

int	lexer(t_data *data)
{
	if (check_quotes(data->input) || check_token(data->input))
		return (1);
	create_list(data, &data->input);
// 	printf("data->input: %s\n", data->input);
// ///
// 	t_lexer *tmp = data->lex;
// 	printf("input str in lexer.c: %s\n", data->input);
// 	while (tmp)
// 	{
// 		printf("nodes in lex: %s=%d ", tmp->word, tmp->token);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// ///
	return (0);
}
