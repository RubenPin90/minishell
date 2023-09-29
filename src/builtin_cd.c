#include "builtin.h"

int	update_path(t_lstenv *env, char *pathname, char *key)
{
	t_lstenv *new_env_node;
	t_lstenv *start;

	start = env;
	if (!env || !pathname || !key)
		return (AGAIN);
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key) + 1))
		{
			env->value = free_null(env->value);
			env->value = ft_strdup(pathname);
			if (!env->value)
				return (FAIL);
			break ;
		}
		env = env->next;
	}
	if (!env)
	{
		new_env_node = lstenv_new(ft_strdup(key), ft_strdup(pathname));
		if (!new_env_node || !new_env_node->key || !new_env_node->value)
			return (FAIL);
		env = start;
		env_addback(&env, new_env_node);
	}
	return (SUCCESS);
}

int	redir_pwd(t_data *data, t_lstenv *env, char *curpwd, char *key)
{
	char *keyvalue;

	keyvalue = find_envkey(env, key);
	if (!keyvalue)
	{
		if (ft_strncmp(key, "HOME", ft_strlen(key)))
			return (error_msg("cd", NULL, CD_HOME_ERR));
		else
			return (error_msg("cd", NULL, CD_OLDPWD_ERR));
	}
	if (changedir(data, env, curpwd, keyvalue))
		return (AGAIN);
	return (SUCCESS);
}

int	changedir(t_data *data, t_lstenv *env, char *curpwd, char *arg)
{
	char	*cwd;
	char	*tmp;
	int		ret;

	if (chdir(arg) == -1)
		return (error_msg("cd", arg, strerror(errno)));
	tmp = get_pwd();
	if (tmp)
		cwd = ft_strdup(tmp);
	if (!tmp || !cwd)
		return (error_msg("cd", NULL, "something went wrong."));
	tmp = free_null(tmp);
	ret = update_path(env, curpwd, "OLDPWD");
	ret = update_path(env, cwd, "PWD");
	cwd = free_null(cwd);
	if (ret == FAIL)
		ft_error(MALLOC_ERR, data);
	return (SUCCESS);
}

int	ft_cd(t_data *data, t_parse *cmd)
{
	int		num_args;
	char	*curpwd;
	int		ret;

	curpwd = NULL;
	num_args = ft_arrlen(cmd->cmd);
	if (num_args > 2)
		return (error_msg("cd", NULL, ARG_ERR));
	curpwd = find_envkey(data->env, "PWD");
	if (num_args == 1 || !ft_strncmp(cmd->cmd[1], "~", 2) || \
						 !ft_strncmp(cmd->cmd[1], "--", 3))
		ret = redir_pwd(data, data->env, curpwd, "HOME");
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
		ret = redir_pwd(data, data->env, curpwd, "OLDPWD");
	else
		ret = changedir(data, data->env, curpwd, cmd->cmd[1]);
	if (ret)
		return (AGAIN);
	return (SUCCESS);
}
