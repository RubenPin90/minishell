#include "error_handling.h"

int	ft_error(char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	if (data)
		ft_cleanup(&data);
	// exit(FAIL);
	return (1);
}

void	ft_cleanup(t_data **data)
{
	if ((*data)->env)
		lstenv_clear(&(*data)->env);
	if ((*data)->input)
		free_null((*data)->input);
}

void	free_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	lstenv_clear(t_lstenv **head)
{
	t_lstenv	*cur;
	t_lstenv	*next;

	cur = *head;
	while (cur)
	{
		next = cur->next;
		free_null((void *)cur->key);
		free_null((void *)cur->value);
		free_null((void *)cur);
		cur = next;
	}
	*head = NULL;
}

char **free_arr(char **arr)
{
	int i;

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
	return (arr);
}
