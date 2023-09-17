#include "builtin.h"

int	save_curpwd(t_data *data, t_lstenv *env, char **oldpwd)
{
	char *tmpvalue;

	tmpvalue = find_envkey(env, "PWD");
	if (!tmpvalue)
		return (AGAIN);
	*oldpwd = ft_strdup(tmpvalue);
	if (!oldpwd)
		ft_error(MALLOC_ERR, data);
	return (SUCCESS);
}


int	ft_cd(t_data *data, t_parse *cmd)
{
	int		num_args;
	char	*oldpwd;

	(void)data;
	(void)cmd;
	oldpwd = NULL;
	num_args = ft_arrlen(cmd->cmd);
	if (num_args > 2)
		return (AGAIN);
	if (save_curpwd(data, data->env, &oldpwd))
		return (error_msg("OLDPWD", "Not found."));
	if (num_args == 1)
		printf("go to HOME\n");
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
		printf("OLDPATH\n");
	else
		printf("changedir\n");
	return (SUCCESS);
}