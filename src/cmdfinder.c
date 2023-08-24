#include <cmdfinder.h>

char *findpath(t_lstenv *env)
{
	while (env)
	{
		if (!ft_strncmp(env->key,"PATH", 5))
			break ;
		env = env->next;
	}
	return (env->value);
}

int	cmdfinder(t_data *data, t_parse *cmd_line)
{
	char *path_line;

	path_line = findpath(data->env);
	data->paths = ft_split(path_line, ':');
	if (!data->paths)
		ft_error(MALLOC_ERR, data);
	while (cmd_line->id != 0)
	{
		if (find_cmd(data, &cmd_line->cmd[0], data->paths))
		{
			data->paths = free_arr(data->paths);
			return (error_msg(cmd_line->cmd[0], NOTFOUND_ERR));
		}
		cmd_line++;
	}
	data->paths = free_arr(data->paths);
	return (0);
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
			return (0);
		}
		*cmdpath = free_null(*cmdpath);
		*cmdpath = cmdname;
	}
	return (1);
}
