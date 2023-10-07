#include "executor.h"

int cmdfinder(t_data *data, t_parse *cmdl)
{
	int ex_status;

	while (cmdl->id != 0)
	{
		ex_status = is_executable(cmdl);
		if (ex_status == SUCCESS)
		{
			if (is_builtin(cmdl, cmdl->cmd[0]) == FAIL)
			{
				is_binary(data, cmdl, &cmdl->cmd_path, cmdl->cmd[0]);
				// data->paths = free_arr(data->paths);
				// error_msg(cmdl->cmd[0], NULL, NOTFOUND_ERR, FAIL);
			}
		}
		else
			set_exstat(cmdl, &cmdl->execute, cmdl->exstatus);
		cmdl++;
	}
	data->paths = free_arr(data->paths);
	return (SUCCESS);
}

int is_binary(t_data *data, t_parse *cmdl, char **cmdpath, char *cmdname)
{
	char	*path_line;

	path_line = NULL;
	if (ft_strchr(cmdname, '/'))
		if (check_dir(cmdl, cmdname))
			return (FAIL);
	if (check_access(data, cmdl, cmdname, cmdpath))
		return (FAIL);
	if (*cmdpath != NULL)
		return (SUCCESS);
	if (cmdname[0] == '\0' || !ft_strncmp(cmdname, ".", 2) || !ft_strncmp(cmdname, "..", 3))
		return (set_exstat(cmdl, &cmdl->execute, E_NOCMD));
	if (!data->paths)
	{
		path_line = find_envkey(data->env, "PATH");
		if (path_line)
		{
			data->paths = ft_split(path_line, ':');
			if (!data->paths)
				ft_error(MALLOC_ERR, data);
		}
	}
	if (find_cmd(data, cmdname, cmdpath, data->paths))
		return (set_exstat(cmdl, &cmdl->execute, E_NOCMD));
	return (SUCCESS);
}

int check_access(t_data *data, t_parse *cmdl, char *cmdname, char **cmdpath)
{
	if (cmdname[0] == '/' || !ft_strncmp(cmdname, "./", 2) || \
		!ft_strncmp(cmdname, "../", 3))
	{
		if (ft_access_wrapper(cmdl, cmdname))
			return (FAIL);
		*cmdpath = ft_strdup(cmdname);
		if (!cmdpath)
			ft_error(MALLOC_ERR, data);
	}
	return (SUCCESS);
}

int	check_dir(t_parse *cmdl, char *cmdname)
{
	struct	stat tmp;
	int		ret;

	ret = stat(cmdname, &tmp);
	if (ret < 0 && errno == ENOENT)
		return (set_exstat(cmdl, &cmdl->execute, E_NOENT));
	else if (ret < 0)
		return (set_exstat(cmdl, &cmdl->execute, E_ERROR));
	if (S_ISDIR(tmp.st_mode))
		return (set_exstat(cmdl, &cmdl->execute, E_ISDIR));
	return (SUCCESS);
}

int find_cmd(t_data *data, char *cmdname, char **cmdpath, char **paths)
{
	int i;

	if (!paths)
	{
		*cmdpath = ft_strjoin("./", cmdname);
		if (ft_access_wrapper(data->cmd_line, *cmdpath) == 0)
			return (SUCCESS);
		*cmdpath = free_null(*cmdpath);
		return (FAIL);
	}
	i = -1;
	while (paths[++i])
	{
		*cmdpath = ft_strjoin_wrapper(paths[i], "/", cmdname);
		if (!*cmdpath)
			ft_error(MALLOC_ERR, data);
		if (ft_access_wrapper(data->cmd_line, *cmdpath) == 0)
			return (SUCCESS);
		*cmdpath = free_null(*cmdpath);
	}
	return (FAIL);
}

int	ft_access_wrapper(t_parse *cmdl, char *cmdname)
{
	int ret;

	ret = access(cmdname, F_OK);
	if (ret < 0)
		return (set_exstat(cmdl, &cmdl->execute, E_NOCMD));
	ret = access(cmdname, X_OK);
	if (ret < 0)
		return (set_exstat(cmdl, &cmdl->execute, E_NOPERMS));
	cmdl->execute = true;
	cmdl->exstatus = E_SUCCESS;
	return (SUCCESS);
}
