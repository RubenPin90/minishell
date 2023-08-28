#include <cmdfinder.h>

char *find_envkey(t_lstenv *env, char *var)
{
	int len;

	len = ft_strlen(var);
	while (env)
	{
		if (!ft_strncmp(env->key, var, len))
			break ;
		env = env->next;
	}
	return (env->value);
}

int	cmdfinder(t_data *data, t_parse *cmd_line)
{
	while (cmd_line->id != 0)
	{
		if (check_buildin(cmd_line, cmd_line->cmd[0]) && \
		check_binary(data, &cmd_line->cmd[0]))
		{
			data->paths = free_arr(data->paths);
			return (error_msg(cmd_line->cmd[0], NOTFOUND_ERR));
		}
		cmd_line++;
	}
	data->paths = free_arr(data->paths);
	return (SUCCESS);
}

int check_binary(t_data *data, char **cmdpath)
{
	char *path_line;

	path_line = find_envkey(data->env, "PATH");
	data->paths = ft_split(path_line, ':');
	if (!data->paths)
		ft_error(MALLOC_ERR, data);
	if (find_cmd(data, cmdpath, data->paths))
		return (FAIL);
	return (SUCCESS);
}

int	find_cmd(t_data *data, char **cmdpath, char **paths)
{
	int		i;
	char	*cmdname;
	char	*tmp;

	i = -1;
	cmdname = *cmdpath;
	while (paths[++i])
	{	
		*cmdpath = ft_strjoin("/", cmdname);
		if (!*cmdpath)
			ft_error(MALLOC_ERR, data);
		tmp = *cmdpath;
		*cmdpath = ft_strjoin(paths[i], *cmdpath);
		tmp = free_null(tmp);
		if (!*cmdpath)
			ft_error(MALLOC_ERR, data);
		if (access(*cmdpath, F_OK | X_OK) == 0)
		{
			cmdname = free_null(cmdname);
			return (SUCCESS);
		}
		*cmdpath = free_null(*cmdpath);
		*cmdpath = cmdname;
	}
	return (FAIL);
}
