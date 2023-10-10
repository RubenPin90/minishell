/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:02:03 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 15:02:49 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_cd(t_data *data, t_parse *cmd)
{
	int		num_args;
	char	*curpwd;
	int		ret;

	curpwd = NULL;
	num_args = ft_arrlen(cmd->cmd);
	if (num_args > 2)
		return (error_msg("cd", NULL, ARG_ERR, E_ERROR));
	curpwd = set_curpwd(data, data->env);
	if (num_args == 1 || !ft_strncmp(cmd->cmd[1], "~", 2) || \
						!ft_strncmp(cmd->cmd[1], "--", 3))
		ret = redir_pwd(data, data->env, curpwd, "HOME");
	else if (!ft_strncmp(cmd->cmd[1], "-", 2))
		ret = redir_pwd(data, data->env, curpwd, "OLDPWD");
	else
		ret = changedir(data, data->env, curpwd, cmd->cmd[1]);
	curpwd = free_null(curpwd);
	if (ret)
		return (E_ERROR);
	return (E_SUCCESS);
}

char	*set_curpwd(t_data *data, t_lstenv *env)
{
	char	*curpwd;

	curpwd = find_envkey(env, "PWD");
	if (curpwd)
		curpwd = ft_strjoin("OLDPWD=", curpwd);
	else
		curpwd = ft_strdup("OLDPWD=");
	if (!curpwd)
		ft_parent_error(MALLOC_ERR, data, data->cmd_line);
	return (curpwd);
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
	int		ret;

	if (chdir(arg) == -1)
		return (error_msg("cd", arg, strerror(errno), E_ERROR));
	cwd = get_pwd();
	if (cwd)
		cwd = ft_strjoin("PWD=", curpwd);
	if (!cwd)
	{
		curpwd = free_null(curpwd);
		ft_parent_error(MALLOC_ERR, data, data->cmd_line);
	}
	ret = update_path(env, curpwd, "OLDPWD");
	ret = update_path(env, cwd, "PWD");
	cwd = free_null(cwd);
	curpwd = free_null(curpwd);
	if (ret == FAIL)
		ft_parent_error(MALLOC_ERR, data, data->cmd_line);
	return (SUCCESS);
}
