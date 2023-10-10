/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:19 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 15:04:20 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	write_args(char **args, int i, int size)
{
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (i < size - 1)
			ft_putstr_fd(" ", 1);
		i++;
	}
	return (SUCCESS);
}

int	skip_nflags(char **args, int i, bool *newline)
{
	int	j;

	while (args[i] && args[i][0] == '-')
	{
		j = 1;
		while (args[i][j] == 'n')
			j++;
		if (args[i][j] != '\0' || j == 1)
			break ;
		*newline = false;
		i++;
	}
	return (i);
}

int	ft_echo(t_data *data, t_parse *cmd)
{
	bool	newline;
	int		num_args;
	int		i;

	i = 1;
	(void)data;
	newline = true;
	num_args = ft_arrlen(cmd->cmd);
	if (num_args > 1)
	{
		i = skip_nflags(cmd->cmd, i, &newline);
		write_args(cmd->cmd, i, num_args);
	}
	if (newline == true)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (SUCCESS);
}
