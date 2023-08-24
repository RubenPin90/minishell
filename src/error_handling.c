#include "error_handling.h"

int	ft_error(char *msg, t_data *data)
{
	ft_putstr_fd(msg, 2);
	if (data)
	{
		ft_cleanup(data, true);
		exit(FAIL);
	}
	return (1);
}

void	ft_cleanup(t_data *data, bool check)
{
	if (data->env && check)
		lstenv_clear(&data->env);
	if (data->paths)
		data->paths = free_arr(data->paths);
	if (data->input)
		data->input = free_null(data->input);
	if (data->lex)
		free_lexer(&data->lex);
	if (data->cmd_line)
		data->cmd_line = free_parser(data->cmd_line);
}

void	*free_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
	return (ptr);
}

void	lstenv_clear(t_lstenv **head)
{
	t_lstenv	*cur;
	t_lstenv	*next;

	cur = *head;
	while (cur)
	{
		next = cur->next;
		cur->key = free_null(cur->key);
		cur->value = free_null(cur->value);
		cur = free_null((void *)cur);
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
