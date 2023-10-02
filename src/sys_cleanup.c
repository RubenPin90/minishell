#include "minishell.h"

void	ft_cleanup(t_data *data, bool check)
{
	if (data->env_arr)
		data->env_arr = free_arr(data->env_arr);
	if (data->paths)
		data->paths = free_arr(data->paths);
	if (data->input)
		data->input = free_null(data->input);
	if (data->lex)
		free_lexer(&data->lex);
	if (data->cmd_line)
		data->cmd_line = free_parser(data->cmd_line);
	if (data->word)
		data->word = free_word(data->word);
	if (check)
	{
		if (data->env)
			lstenv_clear(&data->env);
		if (data->exp_lst)
			free_lexer(&data->exp_lst);
		rl_clear_history();
		exit(data->excode);
	}
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
		arr[i] = free_null(arr[i]);
		i++;
	}
	arr = free_null(arr);
	return (arr);
}

t_word *free_word(t_word *word)
{
	if (word)
	{
		if (word->str)
			word->str = free_null(word->str);
		word = free_null(word);
	}
	return (word);
}
