#include "env.h"

int	print_env(t_data *data)
{
	t_lstenv *lst;

	lst = data->env;
	while (lst)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (SUCCESS);
}

char **list_to_arr(t_data *data, t_lstenv *lst)
{
	int i;
	int j;

	i = lex_len(data->env);
	data->env_arr = ft_calloc(i + 1, sizeof(char *));
	if (!data->env_arr)
		ft_error(MALLOC_ERR, data);
	j = 0;
	while (lst && j <= i)
	{
		data->env_arr[j] = ft_strjoin_wrapper(lst->key, lst->value);
		if (!data->env_arr[j])
			ft_error(MALLOC_ERR, data);
		lst = lst->next;
		j++;
	}
	return (data->env_arr);
}

char *ft_strjoin_wrapper(char *key, char *value)
{
	char *tmp;
	char *str;

	str = ft_strjoin(key, "=");
	if (!str)
		return (NULL);
	tmp = str;
	str = ft_strjoin(str, value);
	if (!str)
	{
		tmp = free_null(tmp);
		return (NULL);
	}
	tmp = free_null(tmp);
	return(str);
}
