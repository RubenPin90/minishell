#include "../inc/lexer.h"

char	*get_word(t_data *data, char *input, t_word *word)
{
	char	*unquoted;
	char	*tmp;
	int		i;

	unquoted = handle_unquoted(data, input, word->i);
	if (!unquoted)
		ft_error(MALLOC_ERR, data);
	if (!word->str)
		word->str = ft_strdup(unquoted);
	else
	{
		tmp = word->str;
		word->str = ft_strjoin(tmp, unquoted);
		tmp = free_null(tmp);
	}
	free(unquoted);
	i = word->i;
	if (input[i] && (input[i] == '"' || input[i] == '\''))
		word->str = handle_quoted(data, input, word, input[i]);
	// printf("word->str in get_word: %s\n", word->str);
	return (word->str);
}

char	*handle_unquoted(t_data *data, char *input, int i)
{
	char	*tmp;

	data->word->start = i;
	while (input[i] && input[i] != ' ' && input[i] != '>' && \
			input[i] != '<' && input[i] != '|' && input[i] != '"' && \
			input[i] != '\'')
	{
		if (input[i] == '$')
		{
			tmp = input;
			input = expander(tmp, &i);
			tmp = free_null(tmp);
		}
		i++;
	}
	data->word->len = i - data->word->start;
	data->word->i = i;
	return (ft_substr(input, data->word->start, data->word->len));
}

char	*handle_quoted(t_data *data, char *input, t_word *word, char quote)
{
	char	*new;
	char	*tmp;
	int		len;
	int		i;

	i = word->i;
	if (input[i] == '$' && quote == '"')
	{
		tmp = input;
		input = expander(tmp, &i);
		free(tmp);
	}
	len = get_quote_len(input, &i, quote);
	// if (!len)
	// 	return (NULL);
	new = ft_substr(input, word->i + 1, len);
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
	i++;
	// printf("%s, last i: %c\n", word->str, input[i]);
	// if (input[i] && (input[i] != '"' && input[i] != '\'' && input[i] != ' '))
	word->i = i;
	if (input[i] && input[i] != ' ' && input[i] != '>' && \
			input[i] != '<' && input[i] != '|') // && input[i] != '"' && 
			// input[i] != '\'')
		word->str = get_word(data, input, word);
	// if (input[i] && (input[i] == '"' || input[i] == '\''))
	// 	word->str = handle_quoted
	// printf("word->str in get_quote: %s\n", word->str);
	return (word->str);
}

int	get_quote_len(char *input, int *i, char quote)
{
	int		len;

	len = 0;
	(*i)++;
	while (input[*i] && input[*i] != quote)
	{
		len++;
		(*i)++;
	}
	return (len);
}

void	skip_space(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}
