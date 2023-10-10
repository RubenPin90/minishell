/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:03:55 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 15:03:56 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_parent(t_parse *cmd_line, char *cmd)
{
	if (!ft_strncmp(cmd, "exit", 5))
		cmd_line->func = &ft_exit;
	else if (!ft_strncmp(cmd, "export", 7))
		cmd_line->func = &ft_export;
	else if (!ft_strncmp(cmd, "cd", 3))
		cmd_line->func = &ft_cd;
	else if (!ft_strncmp(cmd, "unset", 6))
		cmd_line->func = &ft_unset;
	else
		return (FAIL);
	cmd_line->parent = true;
	return (SUCCESS);
}

int	is_builtin(t_parse *cmd_line, char *cmd)
{
	if (!ft_strncmp(cmd, "pwd", 4))
		cmd_line->func = &ft_pwd;
	else if (!ft_strncmp(cmd, "env", 4))
		cmd_line->func = &print_env;
	else if (!ft_strncmp(cmd, "echo", 5))
		cmd_line->func = &ft_echo;
	else
		if (builtin_parent(cmd_line, cmd))
			return (FAIL);
	return (SUCCESS);
}
