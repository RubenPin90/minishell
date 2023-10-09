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
