#include <cmdfinder.h>

int	cmdfinder(t_data *data, t_parse *cmd_line)
{
	t_lstenv *env_head;
	char *path_line;
	char **paths;

	env_head = data->env;
	while (data->env)
	{
		if (!ft_strncmp(data->env->key,"PATH", 5))
		{
			path_line = data->env->value;
			break ;
		}
		data->env = data->env->next;
	}
	data->env = env_head;
	paths = ft_split(path_line, ':');
	if (!paths)
		return (1);
	while (cmd_line->id != 0)
	{
		if (find_cmd(&cmd_line->cmd[0], paths))
			return (1);
		cmd_line++;
	}
	paths = free_arr(paths);
	return (0);
}

int	find_cmd(char **cmdpath, char **paths)
{
	int		i;
	char	*cmdname;
	char	*tmp;

	i = 0;
	cmdname = *cmdpath;
	while (paths[i])
	{	
		*cmdpath = ft_strjoin("/", cmdname);
		if (!*cmdpath)
			return (1);
		tmp = *cmdpath;
		*cmdpath = ft_strjoin(paths[i], *cmdpath);
		tmp = free_null(tmp);
		if (!*cmdpath)
			return (1);
		if (access(*cmdpath, F_OK | X_OK) == 0)
		{
			cmdname = free_null(cmdname);
			return (0);
		}
		*cmdpath = free_null(*cmdpath);
		i++;
	}
	return (2);
}
