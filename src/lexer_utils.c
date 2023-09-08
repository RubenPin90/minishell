#include "../inc/lexer.h"

char	*get_word(t_data *data, char *input, t_word *word)
{
	int		i;
	int		len;
	char	*new;
	char	*tmp;

	i = word->start;
	len = get_len(input, &i, input[i]);
	new = ft_substr(input, word->i, len);
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
	word->i = i;
	if (input[i] && (input[i] == '$' || !hard_cut(input[i])))
		word->str = get_word(data, input, word);
	return (word->str);
}

// char	*get_word(t_data *data, char *input, t_word *word)
// {
// 	char	*unquoted;
// 	char	*tmp;
// 	int		i;

// 	unquoted = handle_unquoted(data, input, word->i);
// 	printf("input in get_word: %s\n", input);
// 	if (!unquoted)
// 		ft_error(MALLOC_ERR, data);
// 	if (!word->str)
// 		word->str = ft_strdup(unquoted);
// 	else
// 	{
// 		tmp = word->str;
// 		word->str = ft_strjoin(tmp, unquoted);
// 		tmp = free_null(tmp);
// 	}
// 	free(unquoted);
// 	i = word->i;
// 	if (input[i] && (input[i] == '"' || input[i] == '\''))
// 		word->str = handle_quoted(data, input, word, input[i]);
// 	return (word->str);
// }

// char	*handle_quoted(t_data *data, char *input, t_word *word, char quote)
// {
// 	char	*new;
// 	char	*tmp;
// 	int		len;
// 	int		i;

// 	i = word->i;
// 	if (input[i] == '$' && quote == '"')
// 	{
// 		tmp = input;
// 		input = expander(tmp, &i);
// 		printf("input quoted: %s\n", input);
// 		free(tmp);
// 	}
// 	len = quoted_len(input, &i, quote);
// 	new = ft_substr(input, word->i + 1, len);
// 	if (!new)
// 		ft_error(MALLOC_ERR, data);
// 	if (!word->str)
// 		word->str = ft_strdup(new);
// 	else
// 	{
// 		tmp = word->str;
// 		word->str = ft_strjoin(tmp, new);
// 		tmp = free_null(tmp);
// 	}
// 	new = free_null(new);
// 	i++;
// 	// printf("%s, last i: %c\n", word->str, input[i]);
// 	// if (input[i] && (input[i] != '"' && input[i] != '\'' && input[i] != ' '))
// 	word->i = i;
// 	if (!hard_cut(input, i))
// 		word->str = get_word(data, input, word);
// 	return (word->str);
// }

// char	*handle_unquoted(t_data *data, char *input, int i)
// {
// 	char	*tmp;

// 	data->word->start = i;
// 	while (!hard_cut(input, i))
// 	{
// 		if (input[i] == '$')
// 		{
// 			tmp = input;
// 			input = expander(tmp, &i);
// 			printf("input unquoted: %s\n", input);
// 			tmp = free_null(tmp);
// 		}
// 		i++;
// 	}
// 	data->word->len = i - data->word->start;
// 	data->word->i = i;
// 	return (ft_substr(input, data->word->start, data->word->len));
// }

int	get_len(char *input, int *i, char quote)
{
	int		len;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		len = quoted_len(input, i, quote);
		// word->start++;
	}
	else
		len = unquoted_len(input, i);
	return (len);
}

int	unquoted_len(char *input, int *i)
{
	int	len;

	len = 0;
	while (!hard_cut(input[*i]))
	{
			len++;
			(*i)++;
	}
	return (len);
}

int	quoted_len(char *input, int *i, char quote)
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

int	hard_cut(char c)
{
	if (c == '"' || c == '\'' || \
		c == '<' || c == '>' || c == '|' || \
		c == ' ')
		return (1);
	return (0);
}
