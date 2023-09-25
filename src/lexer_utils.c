#include "lexer.h"

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
	while (!hard_cut(input[*i]) && input[*i] != '"' && input[*i] != '\'')
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

// int	soft_cut(char c)
// {
// 	if (!c || c == '<' || c == '>' || c == '|' || c == ' ' || \
// 		c == '"' || c == '\'')
// 		return (1);
// 	return (0);
// }

int	hard_cut(char c)
{
	if (!c || c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}
