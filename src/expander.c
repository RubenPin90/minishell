#include "../inc/lexer.h"

char	*expand_input(char *input, char *new, char *value, int var_len)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (input[i] != '$')
	{
		new[i] = input[i];
		i++;
	}
	j = 0;
	while (value[j])
	{
		new[i + j] = value[j];
		j++;
	}
	k = i + var_len;
	while (input[k])
	{
		new[i + j] = input[k];
		i++;
		k++;
	}
	return (new);
}

int	get_var_len(char *input, int i)
{
	while (input[i] && !hard_cut(input[i]))
		i++;
	return (i);
}

char	*expander(t_data *data, char *input)
{
	char 	value[] = "aapostol";
	char 	*new;
	int		var_len;
	int		str_len;
	int		i;

	i = 0;
	(void)data;
	while (input[i])
	{
		if (input[i] == '$')
		{
			if (input[i + 1] == ' ' || input[i + 1] == '"' || 
			input[i + 1] == '\'')
				i++;
			else
			{
				var_len = get_var_len(input, i);
				str_len = ft_strlen(input) - var_len + ft_strlen(value);
				new = (char *)ft_calloc(str_len + 1, sizeof(char));
				if (!new)
					ft_error(MALLOC_ERR, data);
				new = expand_input(input, new, value, var_len);
				i = -1;
				input = new;
			}
		}
		if (input[i])
			i++;
	}
	return (input);
}
