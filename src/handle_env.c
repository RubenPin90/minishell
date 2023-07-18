
#include "minishell.h"

void	print_env(t_lstenv *lst)
{
 	while (lst->next)
	{
		printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
}

t_lstenv *copy_envp(char **env_org)
{
	int			len;
	int			i;
	t_lstenv	*env_list;

	len = 0;
	env_list = NULL;
	i = -1;
	while (env_org[++i])
		env_extract(&env_list, lstenv_new(env_org[i]));
	return (env_list);
}

void	env_extract(t_lstenv **lst, t_lstenv *new)
{
	t_lstenv	*tmp;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_lstenv	*lstenv_new(char *cont)
{
	char		*delimiter;
	t_lstenv	*new;

	delimiter = ft_strchr(cont, '=');
	if (!delimiter)
		return (NULL);
	new = (t_lstenv *) malloc (sizeof(t_lstenv));
	if (!new)
		return (NULL);
	new->key = ft_substr(cont, 0, delimiter - cont);
	if (!new->key)
		return (NULL); //error function
	new->value = ft_strdup(delimiter + 1);
	if (!new->value)
	{
		free(new->key);
		free(new);
		return (NULL); //error function
	}
	new->next = NULL;
	return (new);
}