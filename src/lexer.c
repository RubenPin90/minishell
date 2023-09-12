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

void	add_word(t_data *data, char *input, t_word *word, int *i)
{
	char	*new;
	char	*tmp;
	int		len;

	len = get_len(data, input, i, input[*i]);
	new = ft_substr(input, word->start, len);
	if (!new)
		ft_error(MALLOC_ERR, data);
	if (!word->str)
		word->str = ft_strdup(new);
	else
	{
		tmp = word->str;
		word->str = ft_strjoin(tmp, new);
		tmp = free_null(tmp);
	}
	new = free_null(new);
}

char	*get_word(t_data *data, char *input, t_word *word)
{
	int		i;

	i = word->i;
	word->start = i;
	add_word(data, input, word, &i);
	check_end_quote(input, &i, word);
	word->i = i;
	if (input[i] && !hard_cut(input[i]))
		word->str = get_word(data, input, word);
	i++;
	return (word->str);
}

// reads through input string and copies every word/token into a node
t_lexer	*create_list(t_data *data, char **datainput)
{
	char	*input;
	t_word	*word;

	input = *datainput;
	data->word = ft_calloc(sizeof(t_word), 1);
	data->word->quoted = false;
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

int	lexer(t_data *data)
{
	if (check_quotes(data->input) || check_token(data->input))
		return (1);
	expander(data, data->input);
	create_list(data, &data->input);
	count_lexlst(data->lex);
	print_lexlst(data);
	return (0);
}
