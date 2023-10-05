#include "builtin.h"

int ft_keylen(char *str)
{
	int i;

	i = 0;
	while(str[i] && str[i] != '=')
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

int	update_env(t_lstenv *env, char *arg, t_data *data)
{
	t_lstenv	*exp_arg;
	int			ret;

	ret = 0;
	exp_arg = lstenv_create(arg);
	if (!exp_arg)
		return (FAIL);
	ret = update_path(data, env, exp_arg->value, exp_arg->key);
	lstenv_clear(&exp_arg);
	if (ret == FAIL)
		return (FAIL);
	return (SUCCESS);
}
