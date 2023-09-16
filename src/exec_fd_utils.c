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

int update_fd(t_parse *cmd, char **file)
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
	int fd;

	if (token == APPEND)
		fd = open(file, O_RDWR | O_APPEND | O_CREAT, 0644);
	else if (token == OUTPUT)
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else if (token == INPUT)
		fd = open(file, O_RDONLY);
	else if (token == HEREDOC)
		fd = open(herefile, O_RDONLY);
	if (fd == -1)
		error_msg(file, strerror(errno));
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
