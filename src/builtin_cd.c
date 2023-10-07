#include "builtin.h"

int	ft_cd(t_data *data, t_parse *cmd)
{
	int		num_args;
	char	*curpwd;
	int		ret;

	curpwd = NULL;
	num_args = ft_arrlen(cmd->cmd);
	if (num_args > 2)
		error_msg("cd", NULL, ARG_ERR, E_ERROR);
	curpwd = find_envkey(data->env, "PWD");
	if (num_args == 1 || !ft_strncmp(cmd->cmd[1], "~", 2) || \
						!ft_strncmp(cmd->cmd[1], "--", 3))
		ret = redir_pwd(data, data->env, curpwd, "HOME");
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
		ret = redir_pwd(data, data->env, curpwd, "OLDPWD");
	else
		ret = changedir(data, data->env, curpwd, cmd->cmd[1]);
	if (ret)
		return (FAIL);
	return (SUCCESS);
}

int	redir_pwd(t_data *data, t_lstenv *env, char *curpwd, char *key)
{
	char	*keyvalue;

	keyvalue = find_envkey(env, key);
	if (!keyvalue)
	{
		if (ft_strncmp(key, "HOME", ft_strlen(key)))
			return (error_msg("cd", NULL, CD_HOME_ERR, E_ERROR));
		else
			return (error_msg("cd", NULL, CD_OLDPWD_ERR, E_ERROR));
	}
	if (changedir(data, env, curpwd, keyvalue))
		return (FAIL);
	return (SUCCESS);
}

int	changedir(t_data *data, t_lstenv *env, char *curpwd, char *arg)
{
	char	*cwd;
	char	*tmp;
	int		ret;

	if (chdir(arg) == -1)
		return (error_msg("cd", arg, strerror(errno), E_ERROR));
	tmp = get_pwd();
	cwd = ft_strdup(tmp);
	tmp = free_null(tmp);
	if (!cwd)
		ft_error(MALLOC_ERR, data);
	ret = update_path(data, env, curpwd, "OLDPWD");
	ret = update_path(data, env, cwd, "PWD");
	cwd = free_null(cwd);
	if (ret == FAIL)
		ft_error(MALLOC_ERR, data);
	return (SUCCESS);
}

int	update_path(t_data *data, t_lstenv *env, char *newvalue, char *key)
{
	t_lstenv	*new_env_node;

	if (!env || !newvalue || !key)
		return (AGAIN);
	if (find_n_update(data, env, newvalue, key) == FAIL)
	{
		new_env_node = lstenv_new(ft_strdup(key), ft_strdup(newvalue));
		if (!new_env_node || !new_env_node->key || !new_env_node->value)
			ft_error(MALLOC_ERR, data);
		env_addback(&env, new_env_node);
	}
	return (SUCCESS);
}

int	find_n_update(t_data *data, t_lstenv *env, char *nvalue, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
		{
			env->value = free_null(env->value);
			env->value = ft_strdup(nvalue);
			if (!env->value)
				ft_error(MALLOC_ERR, data);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (FAIL);
}
