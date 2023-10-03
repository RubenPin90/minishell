#include "expander.h"

int	get_var_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i] && !hard_cut(input[i]) && \
			input[i] != '"' && input[i] != '\'')
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

	var = ft_substr(input, start, len);
	if (!var)
		ft_error(MALLOC_ERR, data);
	val = find_envkey(data->env, var);
	var = free_null(var);
	if (val)
		val = ft_strdup(val);
	else
		val = ft_strdup("");
	if (!val)
		ft_error(MALLOC_ERR, data);
	return (val);
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
