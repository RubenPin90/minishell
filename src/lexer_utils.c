#include "../inc/lexer.h"

char	*get_word(t_data *data, char *input, t_word *word)
{
	int		i;
	int		len;
	char	*new;
	char	*tmp;

	i = word->i;
	word->start = i;
	len = get_len(data, input, &i, input[i]);
	// printf(GREEN"input[i]: %c\n"RESET, input[i]);
	// printf("len: %d\n", len);
	// printf("word->start: %d\n", word->start);
	new = ft_substr(input, word->start, len);
	if (!new)
		ft_error(MALLOC_ERR, data);
	// printf("new: %s\n", new);
	// printf(RED"before - word->str: %s, len: %ld\n"RESET, word->str, ft_strlen(word->str));
	if (!word->str)
		word->str = ft_strdup(new);
	else
	{
		tmp = word->str;
		word->str = ft_strjoin(tmp, new);
		tmp = free_null(tmp);
	}
	// printf(YELLOW"after - word->str: %s, len: %ld\n"RESET, word->str, ft_strlen(word->str));
	new = free_null(new);
	// printf(GREEN"word->i: %d\n"RESET, word->i);
	// printf("input[i]: %c, hardcut: %d\n", input[i], hard_cut(input[i]));
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

int	get_len(t_data *data, char *input, int *i, char quote)
{
	int		len;

	if (input[*i] == '"' || input[*i] == '\'')
	{
		len = quoted_len(input, i, quote);
		data->word->start++;
		data->word->quoted = true;
	}
	else
		len = unquoted_len(input, i);
	return (len);
}

int	unquoted_len(char *input, int *i)
{
	int	len;

	len = 0;
	while (!soft_cut(input[*i]))
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

int	soft_cut(char c)
{
	if (!c || c == '<' || c == '>' || c == '|' || c == ' ' || c == '"' || c == '\'')
		return (1);
	return (0);
}

int	hard_cut(char c)
{
	if (!c || c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}
