#include "executor.h"

int cmdfinder(t_data *data, t_parse *cmd_line)
{
	int ex_status;

	while (cmd_line->id != 0)
	{
		ex_status = is_executable(cmd_line);
		if (ex_status == SUCCESS)
		{
			if (is_builtin(cmd_line, cmd_line->cmd[0]) == FAIL &&
				is_binary(data, &cmd_line->cmd_path, cmd_line->cmd[0]) == FAIL)
			{
				data->paths = free_arr(data->paths);
				switch_cmd_status(cmd_line, &cmd_line->execute, cmd_line->exstatus);
				error_msg(cmd_line->cmd[0], NULL, NOTFOUND_ERR, FAIL);
			}
		}
		else
			switch_cmd_status(cmd_line, &cmd_line->execute, cmd_line->exstatus);
		cmd_line++;
	}
	data->paths = free_arr(data->paths);
	return (SUCCESS);
}

int is_binary(t_data *data, char **cmdpath, char *cmdname)
{
	char *path_line;

	if (cmdname[0] == '\0' || !ft_strncmp(cmdname, ".", 2) || !ft_strncmp(cmdname, "..", 3))
		return (FAIL);
	if (ft_strchr(cmdname, '/'))
		if (check_access(data, cmdname, cmdpath) == 0)
			return (SUCCESS);
	path_line = find_envkey(data->env, "PATH");
	if (!path_line)
		return (FAIL);
	if (data->paths)
		data->paths = free_arr(data->paths);
	data->paths = ft_split(path_line, ':');
	if (!data->paths)
		ft_error(MALLOC_ERR, data);
	if (find_cmd(data, cmdname, cmdpath, data->paths))
		return (FAIL);
	return (SUCCESS);
}

int check_access(t_data *data, char *cmdname, char **cmdpath)
{
	int ret;

	ret = open(cmdname, O_RDONLY);
	
	if (access(cmdname, F_OK | X_OK) < 0)
		return (FAIL);
	*cmdpath = ft_strdup(cmdname);
	if (!cmdpath)
		ft_error(MALLOC_ERR, data);
	return (SUCCESS);
}

int find_cmd(t_data *data, char *cmdname, char **cmdpath, char **paths)
{
	int i;

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
