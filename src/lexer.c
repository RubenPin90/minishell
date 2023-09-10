/**
 * @file lexer.c
 * @brief Create lex list
 * 
 */

#include "../inc/lexer.h"

// NOTE: delete this function
void	print_lexlst(t_data *data)
{
	t_lexer	*tmp = data->lex;

	tmp = data->lex;
	while (tmp)
	{
		printf("lex[%d]: %s\n", tmp->i, tmp->word);
		tmp = tmp->next;
	}
}

// reads through input string and copies every word/token into a node
t_lexer	*create_list(t_data *data, char **datainput)
{
	char	*input;
	// char	*lst_word;
	t_word	*word;

	input = *datainput;
	data->word = ft_calloc(sizeof(t_word), 1); // TODO: init with 0
	word = data->word;
	while (input[word->i])
	{
		skip_space(input, &word->i);
		word->type = check_type(input, &(word->i));
		if (word->type == STOP)
			break ;
		skip_space(input, &(word->i));
		get_word(data, input, word);
		add_node(data, word->str, word);
		word->str = free_null(word->str);
		if (word->type == PIPE)
			word->i++;
	}
	*datainput = input;
	return (data->lex);
}

// FIXME: expander, create_list was commented out, quotes need to be handled by lexer_utils
int	lexer(t_data *data)
{
	if (check_quotes(data->input) || check_token(data->input))
		return (1);
	expander(data, data->input);
	create_list(data, &data->input);
	// count_lexlst(data->lex);
	// print_lexlst(data);
	return (0);
}
