
#include "builtin.h"

int	builtin_parent(t_parse *cmd_line, char *cmd, int len)
{
	if (!ft_strncmp(cmd, "exit", len))
		cmd_line->func = &ft_exit;
	else if (!ft_strncmp(cmd, "export", len))
		cmd_line->func = &ft_export;
	else if (!ft_strncmp(cmd, "cd", len))
		cmd_line->func = &ft_cd;
	else if (!ft_strncmp(cmd, "unset", len))
		cmd_line->func = &ft_unset;
	else
		return (FAIL);
	cmd_line->parent = true;
	return (SUCCESS);
}

int	check_builtin(t_parse *cmd_line, char *cmd)
{
	int len;

	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "pwd", len))
		cmd_line->func = &ft_pwd;
	else if (!ft_strncmp(cmd, "env", len))
		cmd_line->func = &print_env;
	else if (!ft_strncmp(cmd, "echo", len))
		cmd_line->func = &ft_echo;
	else 
		if (builtin_parent(cmd_line, cmd, len))
			return (FAIL);
	return (SUCCESS);
}

/*
*/

