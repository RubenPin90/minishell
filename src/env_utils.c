#include "env.h"

int	print_env(t_data *data, t_parse *cmd)
{
	t_lstenv *lst;

	lst = data->env;
	(void)cmd;
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

	i = env_len(data->env);
	data->env_arr = ft_calloc(i + 1, sizeof(char *));
	if (!data->env_arr)
		ft_error(MALLOC_ERR, data);
	j = 0;
	while (lst && j <= i)
	{
		data->env_arr[j] = ft_strjoin_wrapper(lst->key, "=", lst->value);
		if (!data->env_arr[j])
			ft_error(MALLOC_ERR, data);
		lst = lst->next;
		j++;
	}
	return (data->env_arr);
}


char *find_envkey(t_lstenv *env, char *var)
{
	int len;

	len = ft_strlen(var);
	while (env)
	{
		if (ft_strncmp(env->key, var, len + 1) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	env_len(t_lstenv *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	print_env_arr(char **ar)
{
	int i;

	i = 0;
	while(ar[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(ar[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
}
