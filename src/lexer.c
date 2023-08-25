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
void	add_node(t_data *data, int start, int len, int type)
{
	t_lexer	*node;

	if (type == PIPE)
		len = 1;
	node = new_lexer_node(ft_substr(data->input, start, len), type);
	if (!node)
		return ;
	lexer_addback(&data->lex, node);
}

// reads through input string and copies every word/token into a node
t_lexer	*create_list(t_data *data, char *input)
{
	int		i;
	int		start;
	int		len;
	int		type;

	i = 0;
	start = 0;
	while (input[i])
	{
		skip_space(input, &i);
		type = check_type(input, &i);
		if (type == STOP)
			break ;
		skip_space(input, &i);
		start = i;
		// if (input[i] == '"' || input[i] == '\'')
		// 	get_quote(input, &i, input[i]);
		// else
		get_word(input, &i);
		// printf("outside - start: %d, len: %d\n", start, len);
		len = i - start;
		add_node(data, start, len, type);
		if (type == PIPE)
			i++;
	}
	t_lexer *tmp = data->lex;
	while (tmp)
	{
		printf("%s=%d ", tmp->word, tmp->token);
		fflush(NULL);
		tmp = tmp->next;
	}
	printf("\n");
	return (data->lex);
}

int	lexer(t_data *data)
{
	if (check_quotes(data->input) || check_token(data->input))
		return (1);
	create_list(data, data->input);
	return (0);
}
