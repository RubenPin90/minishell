#include "builtin.h"

void	ft_find_n_del(t_lstenv **env, char *arg)
{
	t_lstenv	*current;
	t_lstenv	*tmp;
	t_lstenv	*prev;

	current = *env;
	prev = NULL;
	while (current)
	{
		if (!ft_strncmp(arg, current->key, ft_strlen(current->key) + 1))
		{
			tmp = current->next;
			current->next = NULL;
			lstenv_clear(&current);
			if (!prev)
				*env = tmp;
			else
				prev->next = tmp;
			current = tmp;
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

int	ft_unset(t_data *data, t_parse *cmd)
{
	int		num_args;
	int		i;

	num_args = ft_arrlen(cmd->cmd);
	if (num_args == 1)
		return (SUCCESS);
	i = 1;
	if (cmd->cmd[i][0] == '-')
		return (error_msg("export", "-", INV_OPT_ERR, E_SYNERR));
	while (cmd->cmd[i])
	{
		ft_find_n_del(&data->env, cmd->cmd[i]);
		i++;
	}
	return (SUCCESS);
}
