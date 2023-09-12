#include "../inc/lexer.h"

void	check_end_quote(char *input, int *i, t_word *word)
{
	if (input[*i] + 1 && word->quoted == true && \
		(input[*i] == '"' || input[*i] == '\''))
	{
		word->quoted = false;
		(*i)++;
	}
}

int	get_len(t_data *data, char *input, int *i, char quote)
{
	int		len;

	len = 0;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		(*i)++;
		while (input[*i] && input[*i] != quote)
		{
			len++;
			(*i)++;
		}
		data->word->start++;
		data->word->quoted = true;
	}
	else
	{
		while (!soft_cut(input[*i]))
		{
			len++;
			(*i)++;
		}
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
	if (!c || c == '<' || c == '>' || c == '|' || c == ' ' || \
		c == '"' || c == '\'')
		return (1);
	return (0);
}

int	hard_cut(char c)
{
	if (!c || c == '<' || c == '>' || c == '|' || c == ' ')
		return (1);
	return (0);
}
