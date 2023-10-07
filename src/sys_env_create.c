#include "minishell.h"

t_lstenv	*copy_envp(t_data *data, char **env_org)
{
	int			i;
	t_lstenv	*env_list;

	env_list = NULL;
	i = -1;
	if (env_org == NULL || !env_org[0])
	{
		data->excode = FAIL;
		ft_putendl_fd(NOENV_ERR, 2);
		ft_cleanup(data, true);
	}
	while (env_org[++i])
		env_addback(&env_list, lstenv_create(env_org[i]));
	return (env_list);
}

void	env_addback(t_lstenv **lst, t_lstenv *new)
{
	t_lstenv	*tmp;

	if (*lst == NULL)
		*lst = new;
	else
	{
		tmp = *lst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_lstenv	*lstenv_create(char *cont)
{
	char		*delimiter;
	char		*key;
	char		*value;
	t_lstenv	*new;

	new = NULL;
	delimiter = ft_strchr(cont, '=');
	if (!delimiter)
		return (NULL);
	key = ft_substr(cont, 0, delimiter - cont);
	if (!key)
		return (NULL);
	value = ft_strdup(delimiter + 1);
	if (!value)
	{
		key = free_null(key);
		return (NULL);
	}
	new = lstenv_new(key, value);
	return (new);
}

t_lstenv	*lstenv_new(char *key, char *value)
{
	t_lstenv	*new;

	new = (t_lstenv *)malloc(sizeof(t_lstenv));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}
