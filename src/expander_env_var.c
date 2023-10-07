#include "expander.h"

int	is_token(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

int	check_for_tokens(char *val)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (val[i])
	{
		if (is_token(val[i]))
			count++;
		i++;
	}
	return (count);
}

char	*add_quotes_to_tokens(char *val, int count)
{
	int		len;
	char	*new;
	int		i;
	int		j;

	len = ft_strlen(val) + (count * 2);
	new = ft_calloc(sizeof(char), len + 1);
	i = 0;
	j = 0;
	while (val[i])
	{
		if (is_token(val[i]))
		{
			new[j] = '"';
			j++;
		}
		new[j] = val[i];
		i++;
		j++;
		if (is_token(val[i - 1]))
		{
			new[j] = '"';
			j++;
		}
	}
	return (new);
}
