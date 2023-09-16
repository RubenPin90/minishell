#include "../inc/lexer.h"

char	*expand_input(char *input, int index, char *value, int var_len)
{
	char	*new;
	int		str_len;
	int		i;
	int		j;
	int		k;

	str_len = ft_strlen(input) - var_len + ft_strlen(value);
	// printf("str_len: %d\n", str_len);
	new = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i != index)
	{
		new[i] = input[i];
		i++;
	}
	// printf("new: %s\n", new);
	j = 0;
	while (value[j])
	{
		new[i + j] = value[j];
		j++;
	}
	// printf("new: %s\n", new);
	k = i + var_len;
	while (input[k])
	{
		new[i + j] = input[k];
		i++;
		k++;
	}
	// printf("new: %s\n", new);
	return (new);
}

int	get_var_len(char *input, int i)
{
	int	len;

	len = 0;
	while (input[i] && !soft_cut(input[i]))
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
	if (!val)
		return (ft_strdup(""));
	return (val);
}

void	expander(t_data *data, char *input)
{
	char 	*value;
	char 	*new;
	int		var_len;
	int		i;
	char	*tmp;
	bool	expand;
	bool 	quoted;

	i = 0;
	expand = true;
	quoted = false;
	while (input[i])
	{
		// printf("input[i]: %c\n", input[i]);
		if (input[i] == '"') // || input[i] == '\'')
		{
			if (quoted == false)
				quoted = true;
			else
				quoted = false;
		}
		if (input[i] == '\'' && quoted == false)
		{
			if (expand == true)
				expand = false;
			else
				expand = true;
		}
		// printf("input[i]: %c quoted: %d\n", input[i], quoted);
		// if (input[i] == '$' && input[i + 1] && (input[i + 1] == ' ' || (quoted == true && (input[i + 1] == '"' || input[i + 1] == '\''))))
		// 	;
		if (input[i] == '$' && expand == true && input[i + 1] && !(input[i + 1] == ' ' || (quoted == true && (input[i + 1] == '"' || input[i + 1] == '\''))))
		{
			// if (input[i + 1] && (input[i + 1] == ' ' || input[i + 1] == '"' || 
			// input[i + 1] == '\'') && quoted == false)
			// 	i++;
			// else
			// {
				// printf("i: %d\n", i);
				var_len = get_var_len(input, i);
				value = get_value(data, input, i + 1, var_len - 1);
				if (!value)
					ft_error(MALLOC_ERR, data);
				new = expand_input(input, i, value, var_len);
				if (!new)
					ft_error(MALLOC_ERR, data);
				if (quoted == true)
					quoted = false;
				// printf("new: %s=%p, %ld\n", new, new, ft_strlen(new));
				tmp = input;
				input = new;
				tmp = free_null(tmp);
				data->input = input;
			// }
		}
		if (input[i])
			i++;
	}
}
