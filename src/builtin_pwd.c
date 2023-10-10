/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 15:04:39 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 15:04:40 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

char	*get_pwd(void)
{
	char	*buf;
	int		size;
	char	*ret;

	size = 4000;
	while (size < 8001)
	{
		buf = ft_calloc(sizeof(char), size);
		if (!buf)
			return (NULL);
		ret = getcwd(buf, size);
		if (!ret)
		{
			size *= 2;
			buf = free_null(buf);
		}
		else
			break ;
	}
	return (ret);
}

int	ft_pwd(t_data *data, t_parse *cmd)
{
	char	*buf;

	(void)data;
	(void)cmd;
	buf = get_pwd();
	if (!buf)
		return (error_msg("pwd", NULL, strerror(errno), E_ERROR));
	ft_putstr_fd(buf, 1);
	ft_putstr_fd("\n", 1);
	buf = free_null(buf);
	return (SUCCESS);
}
