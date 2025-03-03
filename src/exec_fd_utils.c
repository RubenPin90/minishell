/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpinchas <rpinchas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:15:33 by rpinchas          #+#    #+#             */
/*   Updated: 2023/10/10 14:24:12 by rpinchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

int	cleanup_fd(int *fd)
{
	if (*fd >= 0)
	{
		if (close(*fd) == -1)
			return (FAIL);
		*fd = -1;
	}
	return (SUCCESS);
}

int	update_fd(t_parse *cmd, char **file)
{
	if (*file && cmd->heredoc)
	{
		unlink(cmd->heredoc);
		cmd->heredoc = free_null(cmd->heredoc);
	}
	else if (!*file && cmd->heredoc)
		cmd->infile = ft_strdup(cmd->heredoc);
	return (SUCCESS);
}

int	ft_open(char *file, t_type token, char *herefile)
{
	int	fd;

	fd = -1;
	if (token == APPEND)
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (token == OUTPUT)
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (token == INPUT)
		fd = open(file, O_RDONLY);
	else if (token == HEREDOC || token == Q_HEREDOC)
		fd = open(herefile, O_RDONLY);
	if (fd == -1)
		error_msg(file, NULL, strerror(errno), E_ERROR);
	return (fd);
}

int	close_all_fds(t_parse *cmd_line)
{
	while (cmd_line->id != 0)
	{
		cleanup_fd(&cmd_line->fd_in);
		cleanup_fd(&cmd_line->fd_out);
		cleanup_fd(&cmd_line->fd_pipes[0]);
		cleanup_fd(&cmd_line->fd_pipes[1]);
		cmd_line++;
	}
	return (SUCCESS);
}

int	switch_stdfd(t_data *data, t_parse *cmd, int *stdfd, bool switch_fd)
{
	int	err;

	if (switch_fd == true)
	{
		stdfd[0] = dup(STDIN_FILENO);
		stdfd[1] = dup(STDOUT_FILENO);
		replace_fd(data, cmd);
	}
	else
	{
		err = ft_dup2(stdfd[0], stdfd[1]);
		cleanup_fd(&stdfd[0]);
		cleanup_fd(&stdfd[1]);
		if (err)
			ft_error(NULL, data);
	}
	return (SUCCESS);
}
