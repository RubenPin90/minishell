#include "expander.h"

int	get_var_len(char *input, int i)
{
	int	len;

	len = 0;
	if (input[i] == '$')
	{
		i++;
		len++;
	}
	while (input[i] && !hard_cut(input[i]) && \
			input[i] != '"' && input[i] != '\'' && \
			input[i] != '$' && input[i] != '/')
	{
		i++;
		len++;
	}
	return (len);
}

char	*get_value(t_data *data, char *input, int start, int len)
{
	char	*var;
	char	*val;
	int		token_count;

	token_count = 0;
	var = ft_substr(input, start, len);
	if (!var)
		ft_error(MALLOC_ERR, data);
	val = find_envkey(data->env, var);
	var = free_null(var);
	if (val)
	{
		token_count = check_for_tokens(val);
		if (token_count)
			val = add_quotes_to_tokens(val, token_count);
		val = ft_strdup(val);
	}
	else
		val = ft_strdup("");
	if (!val)
		ft_error(MALLOC_ERR, data);
	return (val);
}

void	skip_delim(char *input, int *i)
{
	char	quote;

	quote = '\0';
	(*i) += 2;
	skip_space(input, i);
	while (!hard_cut(input[*i]))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			quote = input[*i];
			while (input[*i] != quote)
				(*i)++;
		}
		(*i)++;
	}
}

int	is_quoted_dollarsign(t_data *data, char *input, int i)
{
	if (data->quoted == true && (input[i + 1] == '"' || input[i + 1] == '\''))
		return (1);
	return (0);
}

bool	toggle_bool(bool ian)
{
	if (ian == false)
		ian = true;
	else
		ian = false;
	return (ian);
}
