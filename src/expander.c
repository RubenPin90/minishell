#include "expander.h"

char	*expand_input(char *input, int index, char *value, int var_len)
{
	char	*new;
	int		str_len;
	char	*rest;

	str_len = ft_strlen(input) - var_len + ft_strlen(value);
	new = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (!new)
		return (NULL);
	rest = input + index + var_len;
	ft_strlcpy(new, input, index + 1);
	ft_strlcat(new, value, ft_strlen(new) + ft_strlen(value) + 1);
	ft_strlcat(new, rest, ft_strlen(new) + ft_strlen(rest) + 1);
	return (new);
}

char	*expander_time(t_data *data, char *input, int i)
{
	char	*new;
	char	*value;
	int		var_len;

	if (input[i] == '$' && input[i + 1] == '?')
	{
		var_len = 2;
		value = ft_itoa(data->excode);
		if (!value)
			ft_error(MALLOC_ERR, data);
	}
	else
	{
		var_len = get_var_len(input, i);
		value = get_value(data, input, i + 1, var_len - 1);
	}
	new = expand_input(input, i, value, var_len);
	value = free_null(value);
	if (!new)
		ft_error(MALLOC_ERR, data);
	return (new);
}

char	*expander(t_data *data, char *input)
{
	int		i;
	char	*new;
	char	*tmp;

	i = 0;
	while (input[i])
	{
		if (input[i] == '"')
			data->quoted = toggle_bool(data->quoted);
		if (input[i] == '\'' && data->quoted == false)
			data->expand = toggle_bool(data->expand);
		if (input[i] == '<' && input[i + 1] == '<')
			skip_delim(input, &i);
		if (input[i] == '$' && data->expand == true && input[i + 1] && \
			input[i + 1] != ' ' && !is_quoted_dollarsign(data, input, i))
		{
			new = expander_time(data, input, i);
			data->quoted = false;
			tmp = input;
			input = new;
			tmp = free_null(tmp);
		}
		if (input[i])
			i++;
	}
	return (input);
}
