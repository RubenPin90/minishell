#include <cmdfinder.h>

int	cmdfinder(t_data *data, t_parse *cmd_line)
{
	while (cmd_line->id != 0)
	{
		if (cmd_line->cmd[0] && check_builtin(cmd_line, cmd_line->cmd[0]) && \
		check_binary(data, &cmd_line->cmd_path, cmd_line->cmd[0]))
		{
			data->paths = free_arr(data->paths);
			return (error_msg(cmd_line->cmd[0], NOTFOUND_ERR));
		}
		cmd_line++;
	}
	data->paths = free_arr(data->paths);
	return (SUCCESS);
}

int check_binary(t_data *data, char **cmdpath, char *cmdname)
{
	char *path_line;

	path_line = find_envkey(data->env, "PATH");
	if (!path_line)
		return (FAIL);
	data->paths = ft_split(path_line, ':');
	if (!data->paths)
		ft_error(MALLOC_ERR, data);
	if (find_cmd(data, cmdname, cmdpath, data->paths))
		return (FAIL);
	return (SUCCESS);
}

int	find_cmd(t_data *data, char *cmdname, char **cmdpath, char **paths)
{
	int		i;

	i = -1;
	while (paths[++i])
	{	
		*cmdpath = ft_strjoin_wrapper(paths[i], "/", cmdname);
		if (!*cmdpath)
			ft_error(MALLOC_ERR, data);
		if (access(*cmdpath, F_OK | X_OK) == 0)
			return (SUCCESS);
		*cmdpath = free_null(*cmdpath);
	}
	return (FAIL);
}
