/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:06 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 17:16:04 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_keylen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

void	ft_bubsort(char **ar, t_lstenv *env)
{
	int		len;
	int		i;
	char	*tmp;

	len = env_len(env);
	while (len-- > 1)
	{
		i = 0;
		while (ar[i] && ar[i + 1])
		{
			if (ft_strncmp(ar[i], ar[i + 1], ft_strlen(ar[i + 1])) > 0)
			{
				tmp = ar[i + 1];
				ar[i + 1] = ar[i];
				ar[i] = tmp;
			}
			i++;
		}
	}
	print_env_arr(ar);
}

int	update_env(t_lstenv *env, char *arg)
{
	int			ret;
	char		*key;

	ret = 0;
	key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	if (!key)
		return (FAIL);
	ret = update_path(env, arg, key);
	key = free_null(key);
	if (ret == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	update_path(t_lstenv *env, char *newpath, char *key)
{
	t_lstenv	*new_env_node;
	int			ret;

	if (!env || !newpath || !key)
		return (AGAIN);
	ret = find_n_update(env, newpath, key);
	if (ret == FAIL)
		return (FAIL);
	else if (ret == AGAIN)
	{
		new_env_node = lstenv_create(newpath);
		if (!new_env_node)
			return (FAIL);
		env_addback(&env, new_env_node);
	}
	return (SUCCESS);
}

int	find_n_update(t_lstenv *env, char *nvalue, char *key)
{
	char	*delimiter;

	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
		{
			env->value = free_null(env->value);
			delimiter = ft_strchr(nvalue, '=');
			env->value = ft_strdup(delimiter + 1);
			if (!env->value)
				return (FAIL);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (AGAIN);
}
