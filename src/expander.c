#include "../inc/lexer.h"

// int	find_dsign(char *input)
// {
// 	int	i;

// 	while (input[i] && input[i] != '$')
// 		i++;
// 	return (i);
// }

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
	// printf("new: %s, input[i]: %c, i: %d\n", new, input[i], i);
	j = 0;
	while (value[j])
	{
		new[i + j] = value[j];
		j++;
	}
	// printf("new: %s, new index: %d, value[j]: %c\n", new, i+j, value[j]);
	// printf("input[var_len]: '%c', \n", input[var_len]);
	// printf("var_len: %d\n", var_len);
	k = i + var_len;
	while (input[k])
	{
		new[i + j] = input[k];
		i++;
		k++;
	}
	// printf("new: %s, j: %d\n", new, i + j);
	// printf("new: %ld\n", ft_strlen(new));
	return (new);
}

char	*expander(char *input, int *i)
{
	char 	value[] = "aapostol";
	char 	*new;
	int		var_len;
	int		str_len;
	int		j;

	j = *i; // i is the index of $
	// j = find_dsign(input);
	if (!ft_isalpha(input[j + 1]))
		return (input);
	j++;
	while (ft_isalnum(input[j]))
		j++;
	var_len = j - *i; // j is one index after the variable
	str_len = ft_strlen(input) - var_len + ft_strlen(value);
	new = (char *)ft_calloc(str_len + 1, sizeof(char));
	if (!new)
		return ("Error\n");
	// printf("input: %s, value: %s, var_len: %d\n", input, value, var_len);
	new = expand_input(input, new, value, var_len);
	// printf("new: %s\n", new);
	return (new);
}

// int	main(void)
// {
// 	char *input = "ca$bbb | bla << $EOF";
// 	char *value = "t -e > file1";
// 	char *output = "cat -e > file1 | bla";
// 	int	i;

// 	i = 2;
// 	printf("input: %ld\n", ft_strlen(input));
// 	printf("value: %ld\n", ft_strlen(value));
// 	printf("output: %s = %ld\n", output, ft_strlen(output));
// 	output = expander(input, value, &i);
// 	free(output);
// 	return (0);
// }
