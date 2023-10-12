/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:41:48 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/12 13:46:06 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	fill_word(char *new, t_word *word)
{
	char	*tmp;

	if (!word->str)
		word->str = ft_strdup(new);
	else
	{
		tmp = word->str;
		word->str = ft_strjoin(tmp, new);
		tmp = free_null(tmp);
	}
}

char	*get_word(t_data *data, char *input, t_word *word)
{
	int		i;
	int		len;
	char	*new;

	i = word->i;
	word->start = i;
	len = get_len(data, input, &i, input[i]);
	new = ft_substr(input, word->start, len);
	if (!new)
		ft_error(MALLOC_ERR, data);
	fill_word(new, word);
	new = free_null(new);
	if (input[i] && input[i + 1] && word->quoted == true && \
		(input[i] == '"' || input[i] == '\''))
	{
		word->quoted = false;
		i++;
	}
	word->i = i;
	if (input[i] && !hard_cut(input[i]))
		word->str = get_word(data, input, word);
	i++;
	return (word->str);
}

int	create_list(t_data *data, char **datainput)
{
	char	*input;
	t_word	*word;

	input = *datainput;
	data->word = ft_calloc(sizeof(t_word), 1);
	if (!data->word)
		return (ft_error(MALLOC_ERR, data));
	data->word->quoted = false;
	word = data->word;
	while (input[word->i])
	{
		skip_space(input, &word->i);
		word->type = check_type(input, &(word->i));
		if (word->type == STOP)
			break ;
		skip_token(input, &(word->i));
		skip_space(input, &(word->i));
		get_word(data, input, word);
		add_node(data, word->str, word);
		word->str = free_null(word->str);
		if (word->type == PIPE)
			word->i++;
	}
	*datainput = input;
	return (SUCCESS);
}

int	lexer(t_data *data)
{
	if (check_quotes(data->input) || check_token(data->input))
	{
		data->excode = 2;
		return (AGAIN);
	}
	data->input = expander(data, data->input);
	if (create_list(data, &data->input))
		return (AGAIN);
	count_lexlst(data->lex);
	return (SUCCESS);
}
